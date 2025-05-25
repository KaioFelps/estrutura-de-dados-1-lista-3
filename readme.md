## Guia de Instalação

Para compilar o projeto, é necessário que estejam instalados:
- Rust + Cargo;
- g++, clang++ ou alguma variante;
- vcpkg.

Abra o  arquivo `build.json` e altere o campo `compiler` para o compilador que tiver à disposição. Altere os outros campos conforme for necessário, como por exemplo, os diretórios de bibliotecas.

Inicialize a ferramenta de build por meio do script `./setup-easexx.sh`.

## Compilando
```bash
vcpkg install
./exx build
```

## Rodando os testes
```bash
vcpkg install
./exx test
```
