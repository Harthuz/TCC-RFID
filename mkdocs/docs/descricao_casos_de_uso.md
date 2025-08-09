## Diagrama de Caso de Uso Simplificado

### 2.1. Atores
1. **Gerente** — Consulta e monitora estoque e alertas.
2. **Administrador** — Possui todas as permissões do gerente, além de atualizar estoque e gerenciar credenciais.
3. **Sistema de Prateleira Inteligente (SPI)** — Detecta e envia movimentações de produtos.

### 2.2. Casos de Uso
1. Monitorar Estoque em Tempo Real.
2. Gerenciar Alertas.
3. Consultar Histórico de Movimentações.
4. Atualizar Estoque Manualmente.
5. Autenticar no Sistema.
6. Processar Movimentação de Produto.
7. Gerenciar Credenciais de Acesso.

### 2.3. Relações
1. **Gerente** autentica e acessa monitoramento, alertas e histórico.
2. **Administrador** autentica e acessa todas as funcionalidades do gerente, além de atualizar estoque e gerenciar credenciais.
3. O **SPI** processa movimentações de produto e inclui funcionalidades de monitoramento e alertas.