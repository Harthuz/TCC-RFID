# Fluxos do Sistema de Prateleira Inteligente com RFID

## 1. Fluxo de "Atualizar estoque e gerar alertas" (UC2, UC3, UC4)

Esse diagrama descreve o fluxo de atualização de estoque e geração de alertas a partir dos dados recebidos do microcontrolador.

1. **Recebimento de dados do Microcontrolador**:
   - O backend recebe o ID da tag e o tipo de evento (adição ou remoção).
   
2. **Validação do ID da Tag**:
   - O backend valida se o ID da tag existe no banco de dados.
   - Se o ID for inválido, um erro é registrado e o processo é interrompido.

3. **Atualização de Estoque**:
   - Se a tag for válida, o registro do produto é atualizado no banco de dados.
   - Duas verificações são realizadas em paralelo:
     1. **Verificação de Estoque**:
        - O backend consulta a quantidade mínima de estoque.
        - Se o estoque estiver abaixo do mínimo, um alerta de baixo estoque é enviado ao Sistema de Notificação.
     2. **Verificação de Vencimento**:
        - O backend verifica a data de vencimento do produto.
        - Se o vencimento estiver próximo, um alerta de vencimento é enviado ao Sistema de Notificação.

4. **Confirmação da Atualização**:
   - Após as verificações, a atualização do banco de dados é confirmada e o processo é concluído.

---

## 2. Fluxo de "Consultar histórico de movimentações" (UC7)

Esse diagrama descreve o processo de consulta ao histórico de movimentações de produtos.

1. **Seleção da opção "Histórico de Movimentações"**:
   - O 'Gerente' seleciona a opção **"Histórico de Movimentações"** no dashboard.

2. **Apresentação dos Filtros**:
   - O sistema exibe opções de filtro para consulta: **por data**, **por produto** e **por tipo de evento**.

3. **Escolha dos Filtros**:
   - O 'Gerente' seleciona os filtros desejados de acordo com a necessidade.

4. **Consulta ao Banco de Dados**:
   - O sistema realiza uma consulta ao banco de dados utilizando os filtros selecionados.

5. **Exibição do Histórico**:
   - O sistema exibe o histórico de movimentações filtrado conforme as escolhas do 'Gerente'.

---

## 3. Fluxo de "Gerenciar credenciais de acesso" (UC8)

Esse diagrama descreve o processo de gerenciamento de credenciais de acesso de usuários pelo administrador.

1. **Acesso ao Módulo de Gerenciamento de Usuários**:
   - O 'Administrador' acessa o módulo de gerenciamento de usuários.

2. **Exibição da Lista de Usuários**:
   - O sistema exibe uma lista de usuários existentes.

3. **Escolha de Ação (Adicionar, Editar ou Remover)**:
   O administrador pode realizar três ações:

   1. **Adicionar Novo Usuário**:
      - O 'Administrador' seleciona a opção "Adicionar".
      - O sistema exibe um formulário de cadastro.
      - O 'Administrador' preenche o formulário e salva.
      - O sistema registra o novo usuário e confirma o sucesso.

   2. **Editar Usuário**:
      - O 'Administrador' seleciona um usuário existente para editar.
      - O sistema exibe um formulário com os dados pré-preenchidos.
      - O 'Administrador' modifica os dados e salva.
      - O sistema atualiza as informações do usuário e confirma o sucesso.

   3. **Remover Usuário**:
      - O 'Administrador' seleciona um usuário para remoção.
      - O sistema solicita confirmação para excluir o usuário.
      - O 'Administrador' confirma a exclusão.
      - O sistema exclui o usuário e confirma o sucesso.

---

## 4. Fluxo do Caso de Uso "Identificar produto via RFID" (UC1)

Esse diagrama descreve o processo de identificação de um produto via RFID.

1. **Adição ou Remoção do Produto**:
   - O produto é adicionado ou removido da prateleira.

2. **Detecção pela Leitura RFID**:
   - O leitor RFID detecta a tag do produto.

3. **Captura do ID da Tag**:
   - O leitor RFID captura o ID único da tag do produto.

4. **Envio do ID para o Microcontrolador**:
   - O microcontrolador (ESP32) recebe o ID da tag.

5. **Envio de Dados ao Backend**:
   - O microcontrolador envia o ID da tag e o tipo de evento (adição ou remoção) para o Backend.

---

## 5. Fluxo de "Visualizar Dashboard em Tempo Real" (UC5)

Esse diagrama descreve o processo de visualização do dashboard em tempo real pelo gerente.

1. **Acesso ao Sistema**:
   - O 'Gerente' acessa o sistema.

2. **Verificação de Credenciais**:
   - O sistema verifica as credenciais do 'Gerente'.
   - Essa verificação pode ser realizada pelo backend.

3. **Credenciais Válidas?**:
   - Se as credenciais forem válidas, o sistema procede com a exibição do dashboard:
     1. **Carregamento dos Dados**: O sistema carrega dados de estoque, alertas e histórico em tempo real (usando, por exemplo, Firebase).
     2. **Exibição do Dashboard**: O sistema exibe o dashboard com os dados atualizados.
   - Se as credenciais não forem válidas, o sistema exibe um erro de credenciais e o processo é interrompido.

---

Esses fluxos representam os processos de atualização de estoque, consulta de histórico, gerenciamento de usuários, identificação de produtos e visualização de dados em tempo real, detalhando como cada tarefa ocorre dentro do sistema.
