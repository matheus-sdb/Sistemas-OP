## 1- Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?



**Threads**: A abordagem com threads controla o acesso usando variáveis globais que determinam o tempo que a escada ficará ocupada e a direção de uso. Assim que alguém começa a usar a escada, essas variáveis são atualizadas para bloquear novos acessos até que o tempo estabelecido termine, mantendo a direção fixa. Isso garante que, enquanto alguém estiver utilizando a escada, ninguém mais poderá acessá-la até que seu tempo acabe e a direção só muda quando esse tempo termina.


**Processos**: Na abordagem com processos, a prevenção de acessos simultâneos também utiliza controle de tempo e direção. No entanto, a comunicação entre o processo que gerencia a escada e o principal acontece através de pipes. Isso cria uma camada extra de separação entre os processos, aumentando a segurança dos dados, mas pode trazer mais demora devido à necessidade de enviar informações de volta ao processo principal sempre que houver uma mudança, como a extensão do tempo de ocupação.

## 2- Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?


**Threads**: A direção é gerenciada por uma variável global chamada direction. As threads só mudam essa direção depois que o uso atual termina, o que impede que pessoas em direções opostas tentem usar a escada ao mesmo tempo. A variável é compartilhada e sincronizada entre as threads, garantindo que todos tenham a mesma visão do estado atual.

**Processos**: Para assegurar que somente uma direção seja utilizada de cada vez, o controle é feito por meio de comunicação via pipe. As mudanças de direção são realizadas apenas após o processo filho enviar os dados necessários pelo pipe e o processo pai confirmar o recebimento. Isso evita qualquer sobreposição nas direções de uso, mantendo a operação segura e ordenada.


## 3- Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta

Ao comparar as abordagens usando threads e processos para gerenciar o acesso à escada rolante, encontramos vantagens claras no uso de threads. Threads são mais eficientes por compartilharem o mesmo espaço de memória, o que permite uma sincronização mais rápida e direta de variáveis globais, como o tempo e a direção. Isso reduz o overhead associado à comunicação e à gestão de recursos, tornando a resposta mais rápida.

Em contrapartida, a utilização de processos envolve a comunicação através de pipes, o que pode introduzir atrasos e complicações adicionais. Além disso, cada processo tem seu próprio espaço de memória, o que aumenta o consumo de recursos e pode tornar a coordenação entre eles mais lenta e complexa.

Dessa forma, para o controle de acesso à escada rolante, a implementação com threads mostrou-se mais eficiente. Ela permite um gerenciamento mais ágil e eficaz da concorrência, adaptando-se melhor às necessidades do problema ao minimizar a complexidade e o tempo de resposta.
