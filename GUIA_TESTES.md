# GUIA DE TESTES - CLIENTE Qt

## 🧪 Como testar o cliente antes de entregar

### Pré-requisitos
- Qt Creator com Qt6 instalado
- Python 3.7+ (para servidor de teste)
- Flask (instalar: `pip install flask`)

---

## Opção 1: Teste Completo com Servidor Mock (RECOMENDADO)

### Passo 1: Instalar Flask
```bash
pip install flask
```

### Passo 2: Iniciar o servidor de teste
Na pasta do projeto, abra um terminal e execute:
```bash
python servidor_teste_mock.py
```

Você deve ver:
```
============================================================
SERVIDOR MOCK (TESTE) - MASTER
============================================================
Rodando em: http://localhost:8080

Endpoints disponiveis:
  POST /processar  - Processa arquivo .txt
  GET  /health    - Verifica disponibilidade

Para testar, use o Cliente Qt:
  1. URL do Mestre: http://localhost:8080/processar
  2. Selecione um arquivo .txt
  3. Clique em 'Enviar arquivo ao Mestre'

Pressione Ctrl+C para parar o servidor.
============================================================
```

### Passo 3: Compilar e rodar o cliente
1. Abra o projeto no Qt Creator
2. Compile o projeto (Ctrl+B ou Build → Build)
3. Execute (Ctrl+R ou Build → Run)

### Passo 4: Testar o cliente

**Teste 1: Arquivo de exemplo**
1. URL do Mestre: `http://localhost:8080/processar`
2. Clique em **Selecionar...** e escolha `exemplo_palavras.txt`
3. Clique em **Enviar arquivo ao Mestre**
4. Na resposta JSON, você deve ver:
   ```json
   {
     "resultado": {
       "analise_palavras": {
         "total": 10,
         "unicas": 7,
         "frequencia_top_5": {...}
       },
       "analise_tamanho": {
         "menor": "uva",
         "maior": "abacaxi",
         ...
       }
     }
   }
   ```

**Teste 2: Criar arquivo customizado**
1. Crie um arquivo `teste.txt` com seu próprio conteúdo:
   ```
   python
   java
   javascript
   python
   rust
   go
   ```
2. Repita os passos acima com este arquivo
3. Verifique se a contagem está correta (6 total, 5 únicas)

**Teste 3: Mudar URL do servidor**
1. Modifique a URL para: `http://localhost:9999/processar`
2. Clique em enviar
3. Você deve ver erro: "Falha na requisicao HTTP" com detalhes da conexão
4. Mude para `http://localhost:8080/processar` novamente para funcionar

---

## Teste 2: Health Check (Verificar se servidor está online)

1. Em outro terminal, execute:
```bash
curl http://localhost:8080/health
```

Resposta esperada:
```json
{"status": "disponivel"}
```

---

## Teste 3: Teste via curl (sem GUI)

```bash
# Teste com arquivo
curl -F "arquivo=@exemplo_palavras.txt" http://localhost:8080/processar

# Ou com campo texto
curl -F "texto=banana uva manga banana" http://localhost:8080/processar
```

Resposta esperada (JSON):
```json
{
  "status": "sucesso",
  "resultado": {
    "analise_palavras": {
      "total": 4,
      "unicas": 3,
      "frequencia_top_5": {...}
    },
    "analise_tamanho": {
      "menor": "uva",
      "maior": "banana"
    }
  }
}
```

---

## ✅ Checklist de Testes

- [ ] Servidor mock inicia sem erros
- [ ] Cliente compila sem erros
- [ ] Cliente abre interface gráfica
- [ ] Botão "Selecionar..." abre diálogo de arquivo
- [ ] Campo URL aceita edição
- [ ] Arquivo `exemplo_palavras.txt` é selecionado corretamente
- [ ] Clique em "Enviar arquivo ao Mestre" inicia requisição
- [ ] Status muda para "Enviando arquivo para o Mestre..."
- [ ] Resposta JSON aparece no painel de resultado
- [ ] JSON está formatado (indentado) corretamente
- [ ] Status muda para "Resposta JSON recebida com sucesso."
- [ ] Teste com URL inválida mostra erro
- [ ] Teste sem arquivo selecionado mostra erro
- [ ] Teste com arquivo vazio mostra erro
- [ ] Timeout funciona (aguarde >30s ou teste com IP inexistente)

---

## 🔧 Troubleshooting

| Problema | Solução |
|----------|---------|
| **"qt: could not find the Qt platform plugin"** | Verifique kit Qt6 no Qt Creator |
| **"Failed to connect to localhost:8080"** | Verifique se servidor mock está rodando |
| **"Falha na requisicao HTTP: Connection refused"** | Servidor não está rodando; inicie `servidor_teste_mock.py` |
| **JSON não aparece formatado** | Resposta pode não ser JSON válido; verifique servidor |
| **Arquivo não é lido** | Verifique permissões; tente com caminho absoluto |
| **"ModuleNotFoundError: No module named 'flask'"** | Execute `pip install flask` |

---

## 📊 Output esperado de teste bem-sucedido

```
[16/04/2026 14:23:45] INFO: Arquivo selecionado com sucesso.
[16/04/2026 14:23:50] INFO: Enviando arquivo para o Mestre...
[16/04/2026 14:23:51] INFO: Resposta JSON recebida com sucesso.

Painel de resultado mostra JSON indentado:
{
  "status": "sucesso",
  "resultado": {
    "analise_palavras": {
      "total": 10,
      "unicas": 7,
      "frequencia_top_5": {
        "banana": 2,
        "manga": 2,
        ...
      }
    },
    "analise_tamanho": {
      "menor": "uva",
      "maior": "abacaxi",
      "tamanho_menor": 3,
      "tamanho_maior": 7
    },
    "resumo": {
      "arquivos_processados": 1,
      "thread_1_escravo_1": "OK",
      "thread_2_escravo_2": "OK"
    },
    "timestamp": "2026-04-16T14:23:51.234567"
  }
}
```

---

## 🚀 Conclusão

Se todos os testes passarem, o cliente está **100% funcional** e pronto para ser entregue:
- ✅ Interface gráfica funciona
- ✅ Seleção de arquivo funciona
- ✅ Envio HTTP funciona
- ✅ Recebimento e exibição de JSON funciona
- ✅ Tratamento de erro funciona
- ✅ Sem protótipos, sem bugs

**Você está pronto para passar para o seu amigo fazer o servidor real!**
