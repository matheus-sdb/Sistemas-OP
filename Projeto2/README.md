# Projeto 2 - Sistemas Operacionais

### Matheus Santiago de Brito

### RA: 10408953

# Principais Elementos do Código:
## Definição das Estruturas de Dados:
**Conta**: Representa uma conta bancária com um nome e um saldo.

**Transacao**: Representa uma transação entre duas contas, incluindo a quantia a ser transferida e um contador de transações bem-sucedidas.


## Declaração de Contas e Mutex:
**Conta conta_A; e Conta conta_B;**: Duas contas bancárias iniciais.

**pthread_mutex_t mutex;**: Um mutex para garantir a sincronização das operações de transferência.


## Função de Transferência:
**void *realizar_transferencia(void *argumento)**: Função executada por threads que realiza a transferência de dinheiro entre contas com uso de mutex para evitar condições de corrida.


## Função Principal (main):
Inicializa as contas e o mutex.

Cria várias threads para realizar transações simultâneas.

Aguarda a conclusão de todas as threads.

Exibe o resultado das transações.


## Solução:

O código implementa um sistema de transferência de dinheiro entre duas contas utilizando threads e mutex para garantir a sincronização. A solução destaca-se pela utilização de mutex para evitar condições de corrida, permitindo a execução segura de operações concorrentes em um ambiente multi-thread.
