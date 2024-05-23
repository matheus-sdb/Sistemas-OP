# Projeto 2 - Sistemas Operacionais

### Matheus Santiago de Brito

### RA: 10408953

## Como compilar e executar o programa na plataforma disponibilizada:
```
Instalar o editor vim:
sudo dnf install vim

Abrir e editar o programa com o vim:
vim projeto2.c

Instalar o compilador gcc:
sudo dnf install gcc

Compilar o arquivo .c
gcc -o proj2 projeto2.c

Executar o programa:
./proj2
```

## Como comprovar que os resultados propostos foram alcançados:
![image](https://github.com/matheus-sdb/Sistemas-OP/assets/160658617/f237589d-1ea6-4298-b109-e0a44696d434)
![image](https://github.com/matheus-sdb/Sistemas-OP/assets/160658617/ed11b37e-48ff-4791-913b-c0a4480b4206)

## A solução executada acima cumpre os 5 tópicos abaixo:
1. A conta to pode receber mais de uma transferência simultânea;
2. A conta from pode enviar mais de uma transferência simultânea;
3. A conta from não pode enviar dinheiro se não tiver mais saldo;
4. A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode receber e a conta que recebia pode enviar;
5. Poderão ser realizadas até 100 transações simultâneas de transferência.


# Principais Elementos do Código:
## Definição das Estruturas de Dados:
**Conta**: Representa uma conta bancária com um nome e um saldo.

**Transacao**: Representa uma transação entre duas contas, incluindo a quantia a ser transferida e um contador de transações bem-sucedidas.


## Declaração de Contas e Mutex:
`Conta conta_A; e Conta conta_B;`: Duas contas bancárias iniciais.

`pthread_mutex_t mutex;`: Um mutex para garantir a sincronização das operações de transferência.


## Função de Transferência:
`void *realizar_transferencia(void *argumento)`: Função executada por threads que realiza a transferência de dinheiro entre contas com uso de mutex para evitar condições de corrida.


## Função Principal (main):
Inicializa as contas e o mutex.

Cria várias threads para realizar transações simultâneas.

Aguarda a conclusão de todas as threads.

Exibe o resultado das transações.


## Solução:

O código implementa um sistema de transferência de dinheiro entre duas contas utilizando threads e mutex para garantir a sincronização. A solução destaca-se pela utilização de mutex para evitar condições de corrida, permitindo a execução segura de operações concorrentes em um ambiente multi-thread.
