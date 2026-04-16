@echo off
REM Script para iniciar o servidor Mock de teste no Windows
REM Este servidor simula o Master para testes do Cliente Qt

echo.
echo ============================================================
echo INICIANDO SERVIDOR MOCK (TESTE) - MASTER
echo ============================================================
echo.

REM Detecta se está em um ambiente virtual Python
where python >nul 2>nul
if %errorlevel% neq 0 (
    echo ERRO: Python nao encontrado no PATH
    echo Por favor, instale Python 3.7+ ou adicione ao PATH
    pause
    exit /b 1
)

echo Verificando Flask...
python -c "import flask" >nul 2>nul
if %errorlevel% neq 0 (
    echo Flask nao encontrado. Instalando...
    pip install flask
)

echo.
echo Iniciando servidor em http://localhost:8080
echo.
echo Endpoints disponiveis:
echo   POST /processar  - Processa arquivo .txt
echo   GET  /health    - Verifica disponibilidade
echo.
echo Para PARAR o servidor, pressione Ctrl+C
echo.
echo ============================================================
echo.

REM Inicia o servidor
python servidor_teste_mock.py

pause
