#include <stdio.h>
#include "pico/stdlib.h"   // Inclui a biblioteca padrão para funcionalidades básicas, como GPIO, temporização e comunicação serial.
#include "hardware/timer.h" // Inclui a biblioteca para gerenciamento de temporizadores de hardware.

#define LED_PIN_RED 13     // Define o pino GPIO para o LED vermelho.
#define LED_PIN_BLUE 12    // Define o pino GPIO para o LED azul.
#define LED_PIN_GREEN 11   // Define o pino GPIO para o LED verde.

bool led_red_on = false;   // Variável que indica se o LED vermelho está ligado.
bool led_blue_on = false;  // Variável que indica se o LED azul está ligado.
bool led_green_on = false; // Variável que indica se o LED verde está ligado.

// Definição dos estados do semáforo.
typedef enum {
    VERMELHO,  // Estado do semáforo: Vermelho.
    VERDE,     // Estado do semáforo: Verde.
    AMARELO    // Estado do semáforo: Amarelo.
} EstadoSemaforo;

EstadoSemaforo estadoAtual = VERMELHO; // Inicializa o estado atual do semáforo como Vermelho.

// Função de callback que será chamada repetidamente pelo temporizador.
// O tipo bool indica que a função deve retornar verdadeiro (true) ou falso (false) 
// para continuar ou parar o temporizador, respectivamente.
bool repeating_timer_callback(struct repeating_timer *t) {
    // Imprime uma mensagem na saída serial indicando que 3 segundos se passaram.
    printf("3 segundos passaram\n");

    // Alterna entre os estados do semáforo e atualiza os LEDs correspondentes.
    switch (estadoAtual) {
        case VERMELHO:
            estadoAtual = VERDE;       // Transição para o próximo estado: Verde.
            led_green_on = false;
            led_blue_on = false;
            led_red_on = true;         // Liga o LED vermelho.
            gpio_put(LED_PIN_GREEN, led_green_on);
            gpio_put(LED_PIN_BLUE, led_blue_on);
            gpio_put(LED_PIN_RED, led_red_on);
            break;

        case VERDE:
            estadoAtual = AMARELO;     // Transição para o próximo estado: Amarelo.
            led_green_on = true;       // Liga o LED verde.
            led_blue_on = false;
            led_red_on = false;
            gpio_put(LED_PIN_GREEN, led_green_on);
            gpio_put(LED_PIN_BLUE, led_blue_on);
            gpio_put(LED_PIN_RED, led_red_on);
            break;

        case AMARELO:
            estadoAtual = VERMELHO;    // Transição para o próximo estado: Vermelho.
            led_green_on = false;
            led_blue_on = true;        // Liga o LED azul (representando amarelo).
            led_red_on = false;
            gpio_put(LED_PIN_GREEN, led_green_on);
            gpio_put(LED_PIN_BLUE, led_blue_on);
            gpio_put(LED_PIN_RED, led_red_on);
            break;
    }

    // Retorna true para manter o temporizador repetindo. Se retornar false, o temporizador será interrompido.
    return true;
}

int main() {
    // Inicializa a comunicação serial, permitindo o uso de funções como printf.
    stdio_init_all();

    // Inicializa os pinos GPIO para os LEDs e define sua direção como saída (true).
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, true);

    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, true);

    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, true);

    // Declaração de uma estrutura de temporizador de repetição.
    // Esta estrutura armazenará informações sobre a configuração do temporizador.
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback a cada 3 segundos (3000 ms).
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito que mantém o programa em execução.
    while (true) {
        // Pausa de 1 segundo para reduzir o uso da CPU e permitir mensagens periódicas na saída serial.
        sleep_ms(1000);
        printf("Passou 1 segundo\n");
    }

    return 0;
}
