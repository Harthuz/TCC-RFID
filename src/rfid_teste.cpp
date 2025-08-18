#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <map>

using namespace std;

// Converte bytes da user memory em string limpa
string bytesToProduto(const vector<byte>& data) {
    string result;
    for (byte b : data) {
        if (b >= 32 && b <= 126) result += static_cast<char>(b);
    }
    // remove possíveis zeros extras no final
    size_t end = result.find_last_not_of('\0');
    if (end != string::npos) result = result.substr(0, end + 1);
    return result;
}

int main() {
    const char* portaCOM = "\\\\.\\COM5"; // ajuste sua COM
    HANDLE hSerial = CreateFileA(portaCOM, GENERIC_READ | GENERIC_WRITE, 0, 0,
                                 OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        cerr << "Erro ao abrir porta serial!" << endl;
        return 1;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hSerial, &dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout        = 50;
    timeouts.ReadTotalTimeoutConstant   = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    // Comando mult-tags
    byte comandoMultTags[] = {0xBB, 0x00, 0x27, 0x00, 0x03, 0x22, 0xFF, 0xFF, 0x4A, 0x7E};
    DWORD bytesWritten;

    map<string, chrono::steady_clock::time_point> tagsAtivas;
    const int TEMPO_ESVAZIAR_MS = 800; // tempo para remover tags fora do alcance

    cout << "Leitor pronto! Aproxima as tags..." << endl;

    char buffer[512];
    DWORD bytesRead;

    while (true) {
        WriteFile(hSerial, comandoMultTags, sizeof(comandoMultTags), &bytesWritten, NULL);

        if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
            vector<byte> data(buffer, buffer + bytesRead);
            size_t i = 0;
            while (i < data.size()) {
                if (data[i] == 0xBB) {
                    size_t j = i + 1;
                    while (j < data.size() && data[j] != 0x7E) j++;
                    if (j < data.size()) {
                        vector<byte> pacote(data.begin() + i, data.begin() + j + 1);
                        if (pacote.size() > 10) {
                            size_t start = 7; // User memory começa em 7
                            size_t length = pacote.size() - 9;
                            if (length > 0) {
                                vector<byte> userBytes(pacote.begin() + start, pacote.begin() + start + length);
                                string produto = bytesToProduto(userBytes);
                                if (!produto.empty()) tagsAtivas[produto] = chrono::steady_clock::now();
                            }
                        }
                        i = j + 1;
                    } else break;
                } else i++;
            }
        }

        // remove tags fora do alcance
        auto agora = chrono::steady_clock::now();
        for (auto it = tagsAtivas.begin(); it != tagsAtivas.end();) {
            auto duracao = chrono::duration_cast<chrono::milliseconds>(agora - it->second).count();
            if (duracao > TEMPO_ESVAZIAR_MS) it = tagsAtivas.erase(it);
            else ++it;
        }

        // conta quantas tags de cada produto estão ativas
        map<string, int> contador;
        for (auto& par : tagsAtivas) contador[par.first]++;

        // limpa tela e mostra estoque atual
        cout << "\033[2J\033[1;1H";
        cout << "----- Estoque Atual -----" << endl;
        if (contador.empty()) cout << "Nenhuma tag no alcance" << endl;
        else for (auto& par : contador) cout << par.first << ": " << par.second << " unidades" << endl;
        cout << "-------------------------" << endl;

        this_thread::sleep_for(chrono::milliseconds(50)); // leitura rápida
    }

    CloseHandle(hSerial);
    return 0;
}