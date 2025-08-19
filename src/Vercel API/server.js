const express = require('express');
const bodyParser = require('body-parser');
const swaggerUi = require('swagger-ui-express');
const swaggerJsdoc = require('swagger-jsdoc');

const app = express();
const PORT = 3000;

app.use(bodyParser.json());

// Array para simular o inventário em memória
let inventory = [];

// Swagger setup
const swaggerOptions = {
    definition: {
        openapi: "3.0.0",
        info: {
            title: "API de Inventário RFID",
            version: "1.0.0",
            description: "API para gerenciar produtos via RFID"
        },
        servers: [
            {
                url: "http://localhost:3000",
            },
        ],
    },
    apis: ["./server.js"], // Caminho do arquivo com as anotações
};

const swaggerSpec = swaggerJsdoc(swaggerOptions);
app.use("/api-docs", swaggerUi.serve, swaggerUi.setup(swaggerSpec));

/**
 * @swagger
 * /:
 *   get:
 *     summary: Retorna mensagem de status da API
 *     responses:
 *       200:
 *         description: API funcionando
 */
app.get("/", (req, res) => {
    res.send("API funcionando na Vercel 🚀");
});

/**
 * @swagger
 * /api/produto/adicionar:
 *   post:
 *     summary: Adiciona um produto ao inventário
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             type: object
 *             required:
 *               - rfidTag
 *               - shelfId
 *             properties:
 *               rfidTag:
 *                 type: string
 *               shelfId:
 *                 type: string
 *     responses:
 *       200:
 *         description: Produto adicionado com sucesso
 *       400:
 *         description: Dados inválidos
 */
app.post('/api/produto/adicionar', (req, res) => {
    const { rfidTag, shelfId } = req.body;
    const timestamp = new Date().toISOString();

    if (!rfidTag || !shelfId) {
        return res.status(400).send({ error: 'RFID Tag e Shelf ID são obrigatórios.' });
    }

    const newProduct = { rfidTag, shelfId, status: 'adicionado', timestamp };
    inventory.push(newProduct);

    res.status(200).send({ message: `Produto com tag ${rfidTag} adicionado na prateleira ${shelfId}.` });
});

/**
 * @swagger
 * /api/produto/remover:
 *   post:
 *     summary: Remove um produto do inventário
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             type: object
 *             required:
 *               - rfidTag
 *             properties:
 *               rfidTag:
 *                 type: string
 *     responses:
 *       200:
 *         description: Produto removido com sucesso
 *       400:
 *         description: RFID Tag obrigatório
 *       404:
 *         description: Produto não encontrado
 */
app.post('/api/produto/remover', (req, res) => {
    const { rfidTag } = req.body;
    const timestamp = new Date().toISOString();

    if (!rfidTag) {
        return res.status(400).send({ error: 'RFID Tag é obrigatório.' });
    }

    const productIndex = inventory.findIndex(p => p.rfidTag === rfidTag);
    if (productIndex !== -1) {
        inventory[productIndex].status = 'removido';
        inventory[productIndex].timestamp = timestamp;
        res.status(200).send({ message: `Produto com tag ${rfidTag} removido.` });
    } else {
        res.status(404).send({ error: 'Produto não encontrado.' });
    }
});

/**
 * @swagger
 * /api/inventario:
 *   get:
 *     summary: Retorna o inventário completo
 *     responses:
 *       200:
 *         description: Lista de produtos
 */
app.get('/api/inventario', (req, res) => {
    res.status(200).send(inventory);
});

app.listen(PORT, () => {
    console.log(`Servidor rodando em http://localhost:${PORT}`);
    console.log(`Swagger docs em http://localhost:${PORT}/api-docs`);
});
