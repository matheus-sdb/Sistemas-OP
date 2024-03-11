# EXERCÍCIO 1  //  Matheus Santiago de Brito   RA: 10408953

## Você é capaz de identificar os trechos executados por pai e filho?

Processo filho executa: printf("I am the child %d\n",pid); e execlp("/bin/ls","ls",NULL);.

Processo pai executa: printf("I am the parent %d\n",pid);, wait(NULL);, e printf("Child Complete\n");

## Quantos processos serão criados?

Primeiro fork: Cria 1 processo filho. Total de processos agora: 2

Segundo fork: Processo pai e processo filho criam um novo processo.  Total de processos agora: 4

Terceiro fork: Todos os 4 processos criam um novo processo. Total de processos agora: 8.

Total de processos criados: 8.

## Construa um exemplo, na linguagem C, onde os processos pai e filho trocam algum tipo de mensagem.

![Screenshot_1](https://github.com/matheus-sdb/Sistemas-OP/assets/160658617/e852c1de-3e3f-4164-9d98-7c29f29658af)
