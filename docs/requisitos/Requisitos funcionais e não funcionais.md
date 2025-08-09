### 1. Introdução

O projeto propõe o desenvolvimento de um Sistema de Prateleira Inteligente focado em mercados autônomos. Seu objetivo principal é monitorar e rastrear o comportamento do estoque em tempo real. A finalidade é otimizar a reposição de produtos e evitar perdas por vencimento ou falta de itens nas prateleiras. Este sistema se insere no contexto da automatização de processos comerciais, aproveitando tecnologias como RFID, IoT e Big Data.

### 2. Objetivos do Sistema

O sistema tem como objetivos ser capaz de:
* Identificar produtos que são adicionados ou removidos de uma prateleira.
* Atualizar automaticamente o banco de dados em tempo real com as alterações de inventário.
* Fornecer informações visuais em um dashboard para acompanhamento da situação das prateleiras.
* Emitir alertas sobre a necessidade de reposição e sobre o vencimento de produtos.
* Apresentar um histórico de movimentações.
* Automatizar o controle de estoque.
* Reduzir perdas causadas por vencimento de produtos e falta de reposição.
* Aumentar a rastreabilidade dos produtos.
* Facilitar a gestão do estoque por meio de um dashboard web.

### 3. Tecnologias e Componentes Utilizados

O sistema é construído sobre as seguintes tecnologias e componentes:

* **RFID (Identificação por Rádio Frequência):** Tecnologia fundamental para a identificação automática dos produtos. Cada produto no sistema deve conter uma tag RFID.

* **Leitor RFID:** Dispositivo instalado em cada prateleira que tem a função de detectar as tags RFID presentes nos produtos. Ele é responsável por ler a presença ou ausência das tags.

* **Microcontrolador / Gateway IoT (Ex: ESP32):** Atua como uma ponte entre o hardware (Leitor RFID) e o software de backend. Ele é responsável por capturar os dados brutos enviados pelo leitor RFID e enviá-los para o servidor (backend). O hardware utilizado será o ESP32 WROOM32 integrado a leitores RFID.
 
* **Backend (Node.js):** É a camada de lógica de negócios do sistema. Recebe os dados do microcontrolador, processa-os e gerencia a lógica do sistema, incluindo interações com o banco de dados.
 
* **Banco de Dados (Firebase):** Componente central de armazenamento de dados. Armazena todas as informações do sistema, como o inventário de produtos por prateleira, histórico de movimentações, dados de validade, códigos de produtos e lotes.

* **Frontend (Dashboard em React):** É a interface de usuário do sistema. Exibe as informações em tempo real de forma visual, permitindo o acompanhamento da situação das prateleiras.

* **Sistema de Notificação (Push, Email, SMS ou App):** Módulo responsável por enviar alertas automáticos aos usuários ou operadores do sistema.

### 4. Requisitos Funcionais (RF)

| Código | Descrição                                                                                                 |
| :----- | :-------------------------------------------------------------------------------------------------------- |
| RF01   | Permitir o login dos usuários com autenticação segura.                                                    |
| RF02   | Permitir o cadastro, edição e exclusão de usuários (restrito ao administrador).                           |
| RF03   | Registrar automaticamente a chegada ou retirada de produtos via leitura RFID.                             |
| RF04   | Atualizar o estoque em tempo real com base nas leituras RFID.                                             |
| RF05   | Exibir no dashboard a quantidade atual de produtos por categoria.                                         |
| RF06   | Emitir alertas visuais no dashboard quando um produto estiver em falta.                                   |
| RF07   | Emitir alertas quando um produto estiver próximo da data de vencimento.                                   |
| RF08   | Permitir que o usuário gere relatórios em formato PDF sobre: estoque atual, produtos em falta e validade. |
| RF09   | Permitir a visualização dos dados em gráficos e tabelas.                                                  |
| RF10   | Enviar dados recebidos do ESP32 para o frontend por WebSocket.                                            |
| RF11   | Permitir que administradores realizem manutenções no sistema e ajustes, caso necessário.                  |
| RF12   | Possibilitar a pesquisa e o filtro de produtos dentro do dashboard.                                       |

### 5. Requisitos Não Funcionais (RNF)

| Código | Descrição |
| :--- | :--- |
| RNF01 | O sistema deverá ser responsivo e acessível via navegadores de desktop e dispositivos móveis. |
| RNF02 | O backend deve garantir comunicação segura por meio de HTTPS. |
| RNF03 | As atualizações de estoque devem ser refletidas no dashboard em até 2 segundos após a leitura RFID. |
| RNF04 | O sistema deverá apresentar disponibilidade mínima de 99% quando em produção. |
| RNF05 | A comunicação entre ESP32 e backend deve utilizar protocolos HTTP ou WebSocket, priorizando simplicidade. |
| RNF06 | A autenticação de usuários deve ser segura, com senhas criptografadas e tokens de sessão. |
| RNF07 | O sistema deverá estar hospedado na nuvem, com backups periódicos automáticos. |
| RNF08 | A interface deverá ser intuitiva, visando facilidade de uso para gerentes e repositores. |

### 6. Restrições

* O hardware utilizado será o ESP32 WROOM32 integrado a leitores RFID.
* Para o MVP, a solução será web, sem desenvolvimento específico para aplicativos nativos.
* A ausência de um broker MQTT levou à escolha dos protocolos HTTP ou WebSocket para comunicação IoT.

### 7. Critérios de Aceitação

* O dashboard deverá refletir as mudanças de estoque em tempo real.
* As notificações de produtos vencendo ou em falta devem ser exibidas de forma clara.
* Usuários não autorizados não devem conseguir acessar dados ou funcionalidades restritas.
* A comunicação IoT deverá ser estável e segura.

### 8. Considerações Finais

Este documento define claramente os requisitos necessários para o desenvolvimento do sistema. Ele serve como base para a fase de modelagem (banco de dados, diagramas de processos) e posteriormente para o desenvolvimento. Alterações e adições poderão ser feitas conforme a evolução do projeto.