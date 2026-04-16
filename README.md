# Cliente - Trabalho 04 (Sistemas Distribuidos)

Cliente em C++/Qt (Qt6) para envio de arquivo `.txt` ao servidor Mestre via REST HTTP e exibicao do resultado consolidado retornado em JSON.

## Requisitos atendidos (parte Cliente)

- Interface grafica em C++ com Qt.
- Envio de arquivo `.txt` ao Mestre via HTTP REST.
- Exibicao de resultados retornados pelo Mestre.
- Nenhum processamento de analise das palavras e feito no cliente.

## Estrutura principal

- `main.cpp`: inicializacao da aplicacao Qt.
- `mainwindow.h` / `mainwindow.cpp`: logica da interface e requisicoes HTTP.
- `mainwindow.ui`: layout da interface.
- `CMakeLists.txt`: configuracao do build com Qt Core, Widgets e Network.

## Como executar no Qt Creator

1. Abra a pasta/projeto no Qt Creator.
2. Garanta um kit Qt6 configurado (MinGW ou MSVC).
3. Compile o projeto.
4. Execute o aplicativo.

## Uso do cliente

1. No campo **URL do Mestre**, informe o endpoint de processamento do seu servidor (exemplo: `http://localhost:8080/processar`).
2. Clique em **Selecionar...** e escolha um arquivo `.txt` com uma palavra por linha.
3. Clique em **Enviar arquivo ao Mestre**.
4. Veja no painel de resultado o JSON retornado pelo Mestre.

## Formato de envio HTTP

A requisicao e feita como `multipart/form-data` contendo:

- campo `arquivo`: arquivo `.txt` enviado
- campo `texto`: conteudo textual do arquivo

Isso facilita compatibilidade com diferentes implementacoes do Mestre.

## Exemplo de arquivo de entrada

Use `exemplo_palavras.txt` como teste rapido.

## Observacoes

- O cliente apenas envia dados e exibe resposta.
- Se o Mestre estiver indisponivel ou retornar erro, a mensagem aparece no status e no painel de resultado.
- Timeout de requisicao configurado para 30 segundos.
