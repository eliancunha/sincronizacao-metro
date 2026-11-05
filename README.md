# Implementação 4 — Sincronização do Metrô

## Descrição

Este projeto implementa um mecanismo de sincronização entre passageiros e carros de uma estação de metrô utilizando threads POSIX (Pthreads).

A implementação controla a chegada dos carros, a espera dos passageiros, a autorização para embarque e a confirmação de que os passageiros autorizados embarcaram antes da partida do carro.

## Sistema operacional
- Ubuntu 24.04 LTS (WSL2).


## Arquivos

- `sync_car.c`: implementação das funções de sincronização da estação.
- `sync_car.h`: declaração da estrutura `station` e das funções utilizadas.
- `sync_car-runner.c`: programa de testes fornecido para validar a implementação.
- `Makefile`: instruções para compilação, execução dos testes e limpeza dos arquivos gerados.

## Tecnologias utilizadas

- Linguagem C
- Biblioteca Pthreads
- GCC
- GNU Make

## Compilação

Para compilar o projeto, execute:

```bash
make
```

O comando gera o executável `sync_car`.

## Execução

Para executar o programa de testes:

```bash
make test
```

Se a implementação estiver funcionando corretamente, o runner deverá apresentar a mensagem:

```text
Looks good!
```

## Limpeza

Para remover o executável e os arquivos objeto gerados:

```bash
make clean
```

## Sincronização

A implementação utiliza:

- Um mutex para proteger o estado compartilhado da estação.
- Uma variável de condição para controlar a espera dos passageiros pela chegada de um carro.
- Uma variável de condição para permitir que o carro aguarde a confirmação do embarque dos passageiros.

As operações de espera utilizam `pthread_cond_wait` com reavaliação das condições em laços `while`, evitando que uma thread prossiga sem que os requisitos necessários tenham sido satisfeitos.