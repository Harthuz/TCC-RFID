#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <map>

using namespace std;

// Converte bytes para ASCII imprimível e remove lixo
string bytesToProduto(const vector<byte>& data) {
    string result;
    for (byte b : data) {
        if (b >= 32 && b <= 126) result += static_cast<char>(b);
    }
    // Trunca depois de "Leite 1L" se tiver lixo extra
    size_t pos = result.find("Leite 1L");
    if (pos != string::npos) return "Leite 1L";
    return result;
}

int main() {
    const char* portaCOM = "\\\\.\\COM5"; // Ajuste a sua COM
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

    // Comando para ler User Memory
    byte comandoReadUserMemory[] = {0xBB, 0x00, 0x22, 0x00, 0x00, 0x22, 0x7E};
    DWORD bytesWritten;

    map<string, chrono::steady_clock::time_point> estoque;
    const int TEMPO_ESVAZIAR_MS = 1500; // 1.5s para remover tags fora do alcance

    cout << "Leitor pronto! Aproxima as tags..." << endl;

    char buffer[512];
    DWORD bytesRead;

    while (true) {
        // envia comando para ler User Memory
        WriteFile(hSerial, comandoReadUserMemory, sizeof(comandoReadUserMemory), &bytesWritten, NULL);

        // lê a resposta
        if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
            vector<byte> data(buffer, buffer + bytesRead);

            // procura pacotes BB ... 7E
            size_t i = 0;
            while (i < data.size()) {
                if (data[i] == 0xBB) {
                    size_t j = i + 1;
                    while (j < data.size() && data[j] != 0x7E) j++;
                    if (j < data.size()) {
                        vector<byte> pacote(data.begin() + i, data.begin() + j + 1);
                        if (pacote.size() > 10) {
                            size_t start = 7; // User Memory começa em 7
                            size_t length = pacote.size() - 9;
                            if (length > 0) {
                                vector<byte> userBytes(pacote.begin() + start, pacote.begin() + start + length);
                                string produto = bytesToProduto(userBytes);
                                if (!produto.empty()) estoque[produto] = chrono::steady_clock::now();
                            }
                        }
                        i = j + 1;
                    } else break;
                } else i++;
            }
        }

        // remove tags fora de alcance
        auto agora = chrono::steady_clock::now();
        for (auto it = estoque.begin(); it != estoque.end();) {
            auto duracao = chrono::duration_cast<chrono::milliseconds>(agora - it->second).count();
            if (duracao > TEMPO_ESVAZIAR_MS) it = estoque.erase(it);
            else ++it;
        }

        // mostra estoque atual
        cout << "----- Estoque Atual -----" << endl;
        if (estoque.empty()) cout << "Nenhuma tag no alcance" << endl;
        else for (auto& par : estoque) cout << par.first << " -> Presente" << endl;
        cout << "-------------------------" << endl;

        this_thread::sleep_for(chrono::milliseconds(100));
    }

    CloseHandle(hSerial);
    return 0;
}