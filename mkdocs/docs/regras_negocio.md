# Regras de Negócio do Projeto TCC

## Módulo: Gestão de Estoque e Prateleiras

### 1. Regra de Detecção de Produto (Entrada)
- **Nome da Regra:** RNB-001  
- **Descrição:** O sistema deve registrar a entrada de um produto na prateleira.  
- **Formato (SE-ENTÃO):**  
  SE um leitor RFID detectar uma nova tag que não estava no alcance,  
  ENTÃO o sistema deve registrar a entrada do produto associado a essa tag na prateleira correspondente e atualizar o inventário.

### 2. Regra de Detecção de Produto (Saída)
- **Nome da Regra:** RNB-002  
- **Descrição:** O sistema deve registrar a saída de um produto da prateleira.  
- **Formato (SE-ENTÃO):**  
  SE um leitor RFID deixar de detectar uma tag que estava no seu alcance,  
  ENTÃO o sistema deve registrar a saída do produto associado a essa tag da prateleira e atualizar o inventário.

### 3. Regra de Atualização do Inventário
- **Nome da Regra:** RNB-003  
- **Descrição:** O sistema deve atualizar a quantidade de produtos no banco de dados.  
- **Formato (SE-ENTÃO):**  
  SE a RNB-001 for acionada,  
  ENTÃO o sistema deve incrementar em 1 a quantidade do produto no banco de dados.  
  SE a RNB-002 for acionada,  
  ENTÃO o sistema deve decrementar em 1 a quantidade do produto no banco de dados.

## Módulo: Notificações e Alertas

### 4. Regra de Alerta de Baixo Estoque
- **Nome da Regra:** RNB-004  
- **Descrição:** O sistema deve alertar quando a quantidade de um produto atingir o nível mínimo.  
- **Formato (SE-ENTÃO):**  
  SE a quantidade de um produto na prateleira for igual ou menor que o "nível mínimo" pré-definido,  
  ENTÃO o sistema deve gerar um alerta de baixo estoque para o dashboard e enviar uma notificação push.

### 5. Regra de Alerta de Vencimento
- **Nome da Regra:** RNB-005  
- **Descrição:** O sistema deve alertar sobre produtos com data de validade próxima.  
- **Formato (SE-ENTÃO):**  
  SE a data de validade de um produto for igual ou inferior a um período "X" de dias (ex: 7 dias) a partir da data atual,  
  ENTÃO o sistema deve gerar um alerta de vencimento próximo para o dashboard e enviar uma notificação.

## Módulo: Dashboard e Histórico

### 6. Regra de Visualização do Dashboard
- **Nome da Regra:** RNB-006  
- **Descrição:** O dashboard deve exibir dados de estoque em tempo real.  
- **Formato (SE-ENTÃO):**  
  SE o banco de dados for atualizado com uma movimentação (entrada ou saída),  
  ENTÃO o frontend deve carregar e exibir a nova quantidade de produtos na prateleira em tempo real.

### 7. Regra de Registro Histórico
- **Nome da Regra:** RNB-007  
- **Descrição:** O sistema deve registrar todas as movimentações de produtos.  
- **Formato (SE-ENTÃO):**  
  SE uma movimentação de produto ocorrer (entrada ou saída),  
  ENTÃO o sistema deve registrar no banco de dados a tag do produto, o tipo de movimentação, a data, a hora e a prateleira correspondente.
