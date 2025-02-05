# Projeto: Semáforo com a BitDogLab

Este projeto implementa um **sistema de semáforo** utilizando o microcontrolador **Raspberry Pi Pico W**. O programa controla três LEDs (vermelho, verde e azul) para simular os estados do semáforo: **vermelho**, **verde** e **amarelo** (representado pelo LED azul). A transição entre os estados ocorre a cada 3 segundos, utilizando um temporizador de hardware.

## Funcionalidades

- Controle de LEDs para simular um semáforo.
- Alternância automática entre os estados do semáforo: Vermelho → Verde → Amarelo.
- Utilização de temporizadores de hardware para gerenciar transições.
- Mensagens no terminal serial indicando o tempo decorrido.

## Como Funciona

1. **Estados do Semáforo**:
   - Vermelho: Apenas o LED vermelho acende.
   - Verde: Apenas o LED verde acende.
   - Amarelo: Apenas o LED azul acende.

2. **Transições**:
   - A cada 3 segundos, o estado do semáforo muda automaticamente:
     - Vermelho → Verde → Amarelo → Vermelho.

3. **Temporizador**:
   - Um temporizador de hardware chama a função `repeating_timer_callback()` a cada 3 segundos para alternar entre os estados.

4. **Saída Serial**:
   - Mensagens como "3 segundos passaram" e "Passou 1 segundo" são exibidas no terminal serial para monitoramento.

## Instruções de Uso

1. Compile o código utilizando o SDK do Raspberry Pi Pico W e faça o upload do arquivo `.uf2` para o dispositivo.
2. Ligue a BitDogLab a uma fonte de alimentação USB ou ao computador.
3. Observe os LEDs alternando entre os estados do semáforo: Vermelho → Verde → Amarelo → Vermelho.
4. Para monitorar a execução, conecte-se ao terminal serial (baud rate: 115200) e visualize as mensagens informativas.

