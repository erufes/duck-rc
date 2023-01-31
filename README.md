# duck-rc

## Como executar

Seja a máquina com o controle *Dualshock* conectado a máquina *host* e a Raspberry Pi a máquina *client*.

Os passos 1 e 3 são necessários apenas na primeira vez que o projeto for executado. 

1. Garanta que o Docker esteja instalado na máquina *host*. Clone o repositório para esta máquina.
2. Navegue até a pasta `/containers/ds4_driver` e execute `docker-compose up -d` para iniciar o **serviço de leitura do controle**. Esse serviço é responsável por receber a leitura do controle e publicá-la de forma adequada na rede LAN. Note que a saída da leitura é uma mensagem do tipo [`geometry_msgs/Twist`](https://docs.ros2.org/galactic/api/geometry_msgs/msg/Twist.html).
3. Inicie a Raspberry Pi. Conecte-a à mesma rede da máquina *host*. Instale o [ROS2](https://docs.ros.org/en/humble/index.html) na Raspberry, e clone o repositório para esta máquina. Certifique-se de que o ambiente `ROS2` está ativado. Instale o pacote `python3-colcon-common-extensions` para conseguir "compilar" os nós do projeto. Navegue até a pasta `/ros_ws` e execute `colcon build` para realizar o processo de `build`. Ative os nós compilados na sua sessão com `source install/setup.sh`.
4. Inicie o processo de execução do código na raspberry executando `ros2 run duck bridge`. Isso inicia um processo que aguarda o recebimento de mensagens no tópico `/cmd_vel` e, ao receber essas mensagens, as formata como um arquivo JSON, enviando-o via serial para o Arduino.

Nesse ponto, o robô deve se mover ao usar o controle.
Observação: ocasionalmente pode ser necessário que a raspberry execute um comando de leitura constante da porta serial associada. Para isso, em um outro terminal, execute `tail -F /dev/ttyACM0` - assumindo que a porta serial em questão é a `ttyACM0`.
