# TESTE RÁPIDO (3 PASSOS)

## ✅ Como testar em 3 minutos

### 1️⃣ Inicie o servidor de teste
Duplo clique em `iniciar_servidor_teste.bat`

Você deve ver uma janela com:
```
============================================================
SERVIDOR MOCK (TESTE) - MASTER
============================================================
Rodando em: http://localhost:8080
...
```

**Deixe esta janela aberta.**

---

### 2️⃣ Compile e execute o cliente
1. Abra o projeto no **Qt Creator**
2. Pressione **Ctrl+B** para compilar
3. Pressione **Ctrl+R** para executar

A janela do cliente abrirá com:
- Campo "URL do Mestre" com `http://localhost:8080/processar`
- Botão "Selecionar..." e "Enviar arquivo ao Mestre"

---

### 3️⃣ Faça um teste
1. Clique em **Selecionar...**
2. Escolha `exemplo_palavras.txt`
3. Clique em **Enviar arquivo ao Mestre**
4. Aguarde (deve responder em 1-2 segundos)

**Resultado esperado:**
- Status muda para "Resposta JSON recebida com sucesso."
- Painel mostra JSON formatado com análise de palavras

---

## ✅ Se vir JSON, cliente está 100% funcionando!

---

## 🐛 Se der erro?

| Erro | Solução |
|------|---------|
| Não abre arquivo `.bat` | Clique direito → Editar → Veja se Python está no PATH |
| "Connection refused" | Verifique se servidor_teste_mock.py ainda está rodando |
| "Invalid URL" | Certifique-se que URL é `http://localhost:8080/processar` |
| Qt não compila | Verifique se tem Qt6 installer (MinGW ou MSVC) |

---

## 📋 Testes avançados

Veja arquivo `GUIA_TESTES.md` para testes mais completos.
