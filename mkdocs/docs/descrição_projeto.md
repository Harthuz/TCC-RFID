# Sistema de Prateleira Inteligente com RFID para Mercados Autônomos

## 1. Introdução

O **Sistema de Prateleira Inteligente** visa transformar mercados autônomos por meio de **tecnologias de automação**. O foco principal é **monitorar e rastrear o comportamento do estoque em tempo real**, garantindo **otimização na reposição de produtos** e evitando **perdas por vencimento** ou **falta de itens nas prateleiras**. A proposta é integrar **RFID**, **IoT** e **Big Data** para criar um ambiente de compras mais eficiente e inteligente.

## 2. Objetivos do Sistema

O sistema tem como principais objetivos:

1. **Identificar produtos** ao serem adicionados ou removidos das prateleiras.
2. **Atualizar o banco de dados automaticamente** em tempo real com as movimentações de inventário.
3. Exibir **informações visuais em um dashboard** para acompanhar a situação das prateleiras.
4. **Emitir alertas** sobre a necessidade de reposição e o vencimento de produtos.
5. Apresentar um **histórico completo** de movimentações dos produtos.

## 3. Tecnologias e Componentes Utilizados

Para atingir os objetivos do sistema, diversas tecnologias e componentes são integrados:

1. **RFID (Identificação por Rádio Frequência)**: Usado para a identificação automática dos produtos. Cada produto possui uma tag RFID.
2. **Leitor RFID**: Instalação em cada prateleira para detectar as tags dos produtos.
3. **Microcontrolador / Gateway IoT (ESP32, Raspberry Pi)**: Captura os dados dos leitores RFID e os envia para o backend.
4. **Backend (Node.js, Python Flask/Django)**: Processa os dados recebidos do microcontrolador e gerencia a lógica do sistema.
5. **Banco de Dados (PostgreSQL, Firebase, MongoDB)**: Armazena as informações do sistema, como inventário e histórico de movimentações.
6. **Frontend (React, Angular ou Vue.js)**: Interface do usuário, onde os dados em tempo real são apresentados no dashboard.
7. **Sistema de Notificação**: Envia alertas sobre estoques baixos ou produtos prestes a vencer.

## 4. Funcionamento Detalhado

### 4.1. Adição de Produto na Prateleira

1. **Interação Física**: O produto é adicionado à prateleira, com uma tag RFID associada.
2. **Detecção pelo Leitor RFID**: O leitor detecta a tag do produto.
3. **Transmissão ao Microcontrolador**: O leitor envia o código da tag para o microcontrolador.
4. **Envio para o Backend**: O microcontrolador envia os dados ao backend, incluindo o tipo de evento (adição).
5. **Processamento no Backend**: O sistema verifica a tag e associa o produto à prateleira.
6. **Atualização no Banco de Dados**: O evento de adição é registrado, e a quantidade disponível é atualizada.
7. **Atualização no Dashboard**: O frontend exibe a quantidade atualizada de produtos em tempo real.

### 4.2. Retirada de Produto da Prateleira

1. **Interação Física**: O produto é removido da prateleira.
2. **Perda de Detecção pelo Leitor RFID**: O leitor deixa de detectar a tag do produto.
3. **Transmissão ao Microcontrolador**: O microcontrolador recebe a ausência de detecção.
4. **Envio para o Backend**: A ausência da tag é enviada ao backend.
5. **Processamento no Backend**: O sistema interpreta que houve uma retirada e identifica o produto removido.
6. **Atualização no Banco de Dados**: O banco de dados é atualizado para refletir a retirada, e a quantidade disponível é decrementada.
7. **Atualização no Dashboard**: O frontend atualiza a quantidade de produtos em tempo real.

## 5. Funcionalidades do Sistema

O dashboard exibe em tempo real os produtos disponíveis e a quantidade atual. São enviadas notificações automáticas em casos de baixo estoque, quando a quantidade de um produto atinge o nível mínimo, e de vencimento próximo, quando a data de validade do produto está próxima. O histórico de movimentação registra todas as entradas e saídas de produtos, incluindo data e hora da movimentação, tipo de movimentação (entrada ou retirada).


## 6. Benefícios para Mercados Autônomos

Este sistema oferece uma série de vantagens para mercados autônomos:

1. **Redução de Perdas**: Minimiza perdas por vencimento de produtos.
2. **Eficiência na Reposição**: Permite uma reposição mais rápida e precisa.
3. **Melhoria na Experiência do Cliente**: Garantia de prateleiras sempre abastecidas.
4. **Automatização do Inventário**: Elimina a necessidade de contagens manuais.
5. **Integração com Sistemas de Compra Automática**: Potencial para automatizar compras com fornecedores.

## 7. Considerações Técnicas

Alguns pontos técnicos a serem observados:

1. A **calibração do leitor RFID** é fundamental para evitar leituras duplicadas ou interferências.
2. A comunicação entre o microcontrolador e o backend pode ocorrer via **Wi-Fi**, **Ethernet** ou **LoRa**, dependendo da infraestrutura.
3. O sistema pode ser expandido futuramente para **sensores de peso**, aumentando a precisão no monitoramento de estoque.
4. As **tags RFID** devem armazenar informações essenciais, como:
   - Código do produto.
   - Data de validade.
   - Lote.

---

O **Sistema de Prateleira Inteligente com RFID** é uma solução inovadora para mercados autônomos. Ele oferece **controle em tempo real do estoque**, **redução de perdas** e **eficiência operacional**, proporcionando uma gestão moderna e automatizada do inventário. Integrando **RFID** com **IoT** e **Big Data**, o sistema promete transformar a maneira como os mercados operam, tornando-os mais rápidos, precisos e eficientes.
