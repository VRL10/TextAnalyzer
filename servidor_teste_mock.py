#!/usr/bin/env python3
"""
Servidor Mock (Teste) - Simula o Master para testar o Cliente
Executa em http://localhost:8080/processar

Análise simulada de palavras:
- Conta total e únicas (Escravo 1)
- Identifica mais curta e mais longa (Escravo 2)
"""

from flask import Flask, request, jsonify
import json
from collections import Counter

app = Flask(__name__)

@app.route('/processar', methods=['POST'])
def processar():
    """
    Recebe arquivo .txt via multipart/form-data
    Retorna análise consolidada em JSON
    """
    try:
        # Tenta ler do campo 'arquivo' ou 'texto'
        texto = None
        
        if 'arquivo' in request.files:
            file = request.files['arquivo']
            texto = file.read().decode('utf-8', errors='ignore')
        elif 'texto' in request.form:
            texto = request.form['texto']
        
        if not texto or not texto.strip():
            return jsonify({
                "erro": "Nenhum arquivo ou texto fornecido"
            }), 400
        
        # Processa palavras
        palavras = [p.strip().lower() for p in texto.strip().split() if p.strip()]
        
        if not palavras:
            return jsonify({
                "erro": "Nenhuma palavra encontrada no arquivo"
            }), 400
        
        # Análise 1: Contagem (Escravo 1)
        total_palavras = len(palavras)
        palavras_unicas = len(set(palavras))
        
        # Análise 2: Tamanho (Escravo 2)
        palavra_menor = min(palavras, key=len)
        palavra_maior = max(palavras, key=len)
        
        # Resposta consolidada (JSON)
        resposta = {
            "status": "sucesso",
            "resultado": {
                "analise_palavras": {
                    "total": total_palavras,
                    "unicas": palavras_unicas,
                    "frequencia_top_5": dict(Counter(palavras).most_common(5))
                },
                "analise_tamanho": {
                    "menor": palavra_menor,
                    "maior": palavra_maior,
                    "tamanho_menor": len(palavra_menor),
                    "tamanho_maior": len(palavra_maior)
                },
                "resumo": {
                    "arquivos_processados": 1,
                    "thread_1_escravo_1": "OK",
                    "thread_2_escravo_2": "OK"
                }
            },
            "timestamp": __import__('datetime').datetime.now().isoformat()
        }
        
        return jsonify(resposta), 200
    
    except Exception as e:
        return jsonify({
            "erro": f"Erro ao processar: {str(e)}"
        }), 500

@app.route('/health', methods=['GET'])
def health():
    """Endpoint de health check (conforme enunciado)"""
    return jsonify({"status": "disponivel"}), 200

@app.errorhandler(404)
def nao_encontrado(error):
    return jsonify({"erro": "Endpoint nao encontrado"}), 404

if __name__ == '__main__':
    print("=" * 60)
    print("SERVIDOR MOCK (TESTE) - MASTER")
    print("=" * 60)
    print("Rodando em: http://localhost:8080")
    print()
    print("Endpoints disponiveis:")
    print("  POST /processar  - Processa arquivo .txt")
    print("  GET  /health    - Verifica disponibilidade")
    print()
    print("Para testar, use o Cliente Qt:")
    print("  1. URL do Mestre: http://localhost:8080/processar")
    print("  2. Selecione um arquivo .txt")
    print("  3. Clique em 'Enviar arquivo ao Mestre'")
    print()
    print("Pressione Ctrl+C para parar o servidor.")
    print("=" * 60)
    
    app.run(host='localhost', port=8080, debug=False)
