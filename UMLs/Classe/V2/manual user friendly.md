### **Manual do Sistema – Visão Geral para Usuários**

Este manual explica, de forma simples e não técnica, o que cada parte do sistema faz.
O sistema é dividido em áreas (ou grupos), e dentro de cada uma existem “classes”, que funcionam como partes específicas de um grande conjunto de funções — cada uma com um papel bem definido.

---

## 🧱 **1. models (Modelos)**

**Função:** guardar e buscar informações no banco de dados.
Essas classes são responsáveis por lidar com os dados “reais” do sistema.

### **ProductModel**

* **O que faz:** cuida de tudo que diz respeito aos produtos.
* **Funções principais:**

  * **Buscar histórico:** mostra o que aconteceu com os produtos ao longo do tempo.
  * **Atualizar status:** altera o estado atual de um produto.
  * **Listar produtos:** mostra todos os produtos cadastrados.

---

## 🧭 **2. controllers (Controladores)**

**Função:** fazem a “ponte” entre o que o usuário pede e o que o sistema executa.
Eles recebem pedidos (requisições), tratam as informações e devolvem as respostas certas.

### **ProductController**

* **O que faz:** gerencia tudo que envolve produtos do ponto de vista do sistema.
* **Funções principais:**

  * **Mostrar histórico de produtos.**
  * **Informar o status atual de um produto.**
  * **Verificar se um produto está vencido.**
  * **Classificar o produto de acordo com o estoque.**
  * **Resumir a situação geral dos produtos.**

### **IotController**

* **O que faz:** trata as informações vindas de dispositivos IoT.
* **Função principal:**

  * **Atualizar histórico de produtos** conforme os dados que chegam automaticamente desses dispositivos.

---

## ⚙️ **3. services (Serviços)**

**Função:** lidar com partes técnicas que auxiliam o funcionamento geral do sistema.
Esses serviços não lidam diretamente com usuários, mas tornam possível a comunicação entre partes diferentes do sistema.

### **SocketService**

* **O que faz:** permite que o sistema envie informações em tempo real.
* **Funções principais:**

  * **Ativar a comunicação em tempo real.**
  * **Enviar mensagens automáticas para todos os usuários conectados**

---

## 🔐 **4. middlewares (Intermediários de segurança)**

**Função:** proteger o sistema antes de permitir o acesso a determinadas funções.
São como “porteiros” que verificam se o usuário tem autorização para entrar.

### **Auth**

* **O que faz:** verifica se a chave de acesso (API key) usada é válida.

  * Se for válida, o sistema continua.
  * Se não for, o acesso é bloqueado.

---

## 🛣️ **5. routes (Rotas)**

**Função:** definem os “caminhos” que o sistema segue quando o usuário faz um pedido.
São como os endereços que direcionam cada solicitação para o controlador correto.

### **IotRoutes**

* **O que faz:** recebe as informações vindas de dispositivos inteligentes e as envia para o `IotController`.

### **ProductRoutes**

* **O que faz:** recebe pedidos relacionados a produtos (como listar, consultar ou atualizar) e os envia para o `ProductController`.

---

## 💾 **6. config (Configuração)**

**Função:** centraliza as configurações técnicas do sistema, como a conexão com o banco de dados.

### **DB**

* **O que faz:** mantém e gerencia a conexão com o banco de dados.
  É onde o sistema realmente busca ou grava informações.

---

## 🌐 **7. Server (Servidor)**

**Função:** é o coração do sistema.
Ele liga todas as partes — rotas, controladores, modelos e serviços — para que trabalhem juntas.

### **Server**

* **O que faz:** inicia o sistema, recebe pedidos dos usuários e envia respostas.
* **Funções principais:**

  * **Ativar o servidor na internet (ou rede interna).**
  * **Registrar as rotas (os caminhos de acesso).**
  * **Iniciar a comunicação em tempo real.**
  * **Aplicar as verificações de segurança (middlewares).**

---

### **Resumo do funcionamento geral**

1. O **usuário** (ou um dispositivo) faz um pedido → o pedido chega a uma **rota**.
2. A **rota** envia o pedido para o **controlador** correto.
3. O **controlador** conversa com os **modelos** (para buscar ou salvar dados) e com os **serviços** (para tarefas técnicas).
4. As informações voltam, passam pelo **servidor** e retornam ao usuário.
5. O **middleware Auth** garante que apenas acessos autorizados sejam aceitos.