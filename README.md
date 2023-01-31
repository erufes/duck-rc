# duck-rc

## Resumo
<div align="justify">
O projeto consiste em construir um carro operado por controle remoto (DualShock 4) onde a comunicação será feita via Wi-Fi. O sistema será embarcado utilizando uma Raspberry Pi, com os dados enviados a partir de um computador utilizando a framework ROS.
</div>

## Descrição Completa
<div align="justify">
  A ideia principal deste projeto se baseia na construção de um carrinho que é controlado remotamente através de um controle de PlayStation 4 - DualShock 4. A comunicação é feita via Wi-Fi, com os dados do controle sendo coletados e processados por um computador externo ao sistema do carrinho. O framework ROS - Robot Operating System é utilizado para desenvolvimento do código referente a parte de comunicação e processamento de dados que o carro utiliza. ROS é uma framework que viabiliza a comunicação entre diferentes dispositivos por meio de um protocolo de comunicação padronizado, além de disponibilizar, em alguns casos, bibliotecas parcialmente prontas para o desenvolvimento. O funcionamento do sistema como um todo é modelado usando um grafo, no qual cada nó é um componente separado e as arestas representam o fluxo de dados dentro desse sistema:
</div>

<div align="center">

![Esquemático de ROS do robô](/docs/imgs/esquematico_ros.png)

</div>
<div align="justify">
  Da estrutura e funcionamento geral do robô, o ponto principal é a Raspberry, encarregada da comunicação com o computador externo e também do controle geral do carro. A escolha da Raspberry é adequada à medida que ela possui um poder de processamento adequado para o problema, além de possuir conectividade direta via Wi-Fi, conforme necessário a partir das especificações iniciais do projeto. Conforme detectado experimentalmente, a interface GPIO da Raspberry não é adequada para o controle dos motores - dessa forma, foi decidido usar um Arduino Mega 2560.

  Além disso, a escolha dos componentes também é indissociável do projeto “principal” a ser desenvolvido futuramente (embora ele fuja do escopo desta disciplina) - que é, também, um projeto de conclusão de curso. O objetivo final do projeto é desenvolver um carro autônomo em miniatura para participação na Duckietown - uma competição focada na área de inteligência artificial aplicada. Dessa forma, este projeto é, na verdade, uma etapa intermediária em direção ao projeto final.
  
  O robô construido possui dois andares - o superior, que abriga o Arduino Mega, a H-Bridge e alguns fios ligados a uma mini protoboard, e o inferior, que leva a Raspberry, a bateria Li-Po e os motores. Com isso, é possível otimizar o espaço e realizar um projeto simplificado e mais organizado quando comparado com um robô com um único andar.
  
  Para realizar a comunicação entre a Raspberry e o Arduino Mega, utilizou-se um cabo USB da Raspberry para o Arduino. Dessa forma, o Arduino pode ler tudo que a Raspberry escreve na porta serial e interpretar o que estiver escrito como informações do que fazer com os motores. A ligação dos pinos de controle do Arduino com a H-Bridge é responsável por distribuir a potência dos motores e controlar a direção final que o carrinho deve ir.
</div>

// infográfico de como funciona os eixos, a potencia, etc

![Curva de resposta dos motores](/docs/imgs/diagrama_resposta.png)

## Como executar
<div align="justify">
Seja a máquina com o controle *Dualshock* conectado a máquina *host* e a Raspberry Pi a máquina *client*.

Os passos 1 e 3 são necessários apenas na primeira vez que o projeto for executado. 

1. Garanta que o Docker esteja instalado na máquina *host*. Clone o repositório para esta máquina.
2. Navegue até a pasta `/containers/ds4_driver` e execute `docker-compose up -d` para iniciar o **serviço de leitura do controle**. Esse serviço é responsável por receber a leitura do controle e publicá-la de forma adequada na rede LAN. Note que a saída da leitura é uma mensagem do tipo [`geometry_msgs/Twist`](https://docs.ros2.org/galactic/api/geometry_msgs/msg/Twist.html).
3. Inicie a Raspberry Pi. Conecte-a à mesma rede da máquina *host*. Instale o [ROS2](https://docs.ros.org/en/humble/index.html) na Raspberry, e clone o repositório para esta máquina. Certifique-se de que o ambiente `ROS2` está ativado. Instale o pacote `python3-colcon-common-extensions` para conseguir "compilar" os nós do projeto. Navegue até a pasta `/ros_ws` e execute `colcon build` para realizar o processo de `build`. Ative os nós compilados na sua sessão com `source install/setup.sh`.
4. Inicie o processo de execução do código na raspberry executando `ros2 run duck bridge`. Isso inicia um processo que aguarda o recebimento de mensagens no tópico `/cmd_vel` e, ao receber essas mensagens, as formata como um arquivo JSON, enviando-o via serial para o Arduino.

Nesse ponto, o robô deve se mover ao usar o controle.
Observação: ocasionalmente pode ser necessário que a raspberry execute um comando de leitura constante da porta serial associada. Para isso, em um outro terminal, execute `tail -F /dev/ttyACM0` - assumindo que a porta serial em questão é a `ttyACM0`.
</div>
  
## Outros Esquemáticos

O esquemático abaixo mostra os eixos assumidos pelo sistema no código. Note que isso implica em uma transformação linear dos dados recebidos do controle, que mapeiam aceleração de -2 a 2 no eixo x, em uma aceleração de -1 a 1 no eixo y, dentre outros ajustes necessários.

![Eixos assumidos do robô](/docs/imgs/eixos_robo.png)
