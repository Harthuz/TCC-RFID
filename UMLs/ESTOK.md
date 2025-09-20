## 1. Introdução

Este documento apresenta uma análise detalhada do sistema de gerenciamento de estoque, baseada nos diagramas UML fornecidos. O sistema utiliza tecnologia RFID para automatizar o controle de entrada e saída de produtos, fornecendo dados em tempo real para um dashboard gerencial e emitindo alertas automáticos.

## 2. Atores do Sistema

Com base nos diagramas de caso de uso, os seguintes atores foram identificados:

*   **Gerente (Ator Primário):** Responsável por monitorar o estoque, visualizar o histórico de movimentações e receber notificações.
*   **Administrador (Ator Primário):** Responsável pelo gerenciamento de credenciais de acesso ao sistema.
*   **Funcionário (Ator Primário):** Interage com o sistema para visualizar informações sobre produtos.
*   **Sistema de Prateleira Inteligente (Ator Secundário):** O componente de hardware (Leitor RFID + Microcontrolador) que detecta a movimentação de produtos.
*   **Backend (Ator Secundário):** O servidor que processa os dados recebidos do hardware, atualiza o banco de dados e se comunica com o frontend.
*   **Banco de Dados (Ator Secundário):** Armazena todas as informações do sistema, como produtos, estoque, histórico e usuários.
*   **Sistema de Notificação (Ator Secundário):** Responsável por enviar alertas para os usuários.

## 3. Casos de Uso

Os diagramas de caso de uso (simplificado e técnico) descrevem as principais funcionalidades do sistema.

### 3.1. Casos de Uso Simplificados

*   **Gerenciar Funcionários:** Permite ao gerente gerenciar os usuários do sistema.
*   **Visualizar Quantidade de Produtos:** Permite ao funcionário visualizar a quantidade de produtos em estoque.
*   **Receber Notificação de Produto Perto da Validade:** O funcionário é notificado quando um produto está próximo da data de vencimento.
*   **Receber Notificação de Produto Acabando:** O funcionário é notificado quando um produto está com baixo estoque.
*   **Visualizar Histórico de Movimentação:** Permite ao funcionário visualizar o histórico de movimentação de produtos.
*   **Registrar Entrada/Saída de Produtos:** O Leitor RFID registra a entrada e saída de produtos.

### 3.2. Casos de Uso Técnicos

*   **Detecção e Gerenciamento de Alteração de Estoque:** O sistema de prateleira inteligente detecta a adição ou remoção de produtos e envia os dados para o backend.
*   **Processamento e Persistência de Dados de Estoque:** O backend recebe os dados do leitor RFID, processa as informações e as persiste no banco de dados.
*   **Geração e Envio de Alertas:** O backend gera alertas de baixo estoque e de vencimento próximo, e os envia através do sistema de notificação.
*   **Visualização de Dados em Tempo Real:** O gerente pode visualizar o status do estoque, alertas e histórico de movimentações em um dashboard.
*   **Gerenciamento de Credenciais de Acesso:** O administrador pode adicionar, editar e remover usuários do sistema.

## 4. Diagrama de Classes

O diagrama de classes descreve a estrutura do sistema, incluindo as classes de domínio e as classes técnicas.

*   **Classes de Domínio:** `Produto`, `Estoque`, `Alerta`, `Gerente`.
*   **Classes Técnicas:** `LeitorRFID`, `ESP32`, `Backend`, `BancoDeDados`, `Dashboard`, `SistemaNotificacao`.

As relações entre as classes indicam como os diferentes componentes do sistema interagem. Por exemplo, o `Backend` se comunica com o `BancoDeDados`, o `Dashboard` e o `SistemaNotificacao`.

## 5. Diagramas de Atividade

Os diagramas de atividade detalham o fluxo de trabalho de casos de uso específicos.

*   **Identificar produto via RFID:** Descreve como o leitor RFID captura o ID da tag de um produto e o envia para o backend.
*   **Atualizar estoque no banco de dados:** Mostra como o backend atualiza o estoque e gera alertas de baixo estoque ou de vencimento.
*   **Visualizar Dashboard em Tempo Real:** Detalha como o gerente acessa o dashboard e visualiza os dados do sistema.
*   **Consultar histórico de movimentações:** Descreve como o gerente pode filtrar e visualizar o histórico de movimentações de produtos.
*   **Gerenciar credenciais de acesso:** Mostra como o administrador pode gerenciar os usuários do sistema.

## 6. Diagrama de Sequência

O diagrama de sequência "Detecção e Gerenciamento de Alteração de Estoque" ilustra a interação entre os diferentes componentes do sistema ao longo do tempo. Ele mostra como uma alteração física na prateleira (adição ou remoção de um produto) desencadeia uma série de eventos, desde a leitura da tag RFID até a atualização do dashboard e o envio de notificações.

## 7. Conclusão

A análise dos diagramas UML revela um sistema de gerenciamento de estoque bem estruturado e abrangente. A utilização de RFID para automação da coleta de dados, combinada com um backend para processamento e um dashboard para visualização em tempo real, proporciona uma solução eficiente para o controle de estoque. Os diagramas de atividade e de sequência fornecem uma compreensão clara dos fluxos de trabalho do sistema, enquanto o diagrama de classes define a arquitetura de software.
