#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "hardware/timer.h"
#include "LED.pio.h"
#include "funcoes/mudar_LED.c"
#include "numeros/desenho.c"
#include "numeros/cores.c"
// Verifica se passou tempo suficiente desde o último evento

const uint LED_VERMELHO = 13;//LED vermelho que irá piscar de forma intermitente 
const uint button_A = 5;//Porta do botão que irá decrementar o contador
const uint button_B = 6;//Porta do botão que irá incrementar o contador
#define tempo 100//Tempo de ativação do LED Vermelho 
#define OUT_PIN 7//Pino da matriz de LEDs

static volatile uint cont = 0;//Variavel que define o número que será mostrado
static volatile uint cor = 0;//Variavel que define a cor do número que será mostrado
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
static float intensidade = 0.2;//Define a intensidade do brilho dos LEDs
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b);

// Prototipação da função de interrupção
static void gpio_irq_handler(uint gpio, uint32_t events);

//função principal
int main()
    {   
    //Configurações da PIO
    static PIO pio = pio0; 
    uint16_t i;
    uint32_t valor_led;

    //coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    bool ok = set_sys_clock_khz(128000, false);

    // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
    stdio_init_all();
    //Configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    
    // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
    stdio_init_all();

    //Inciailizando e configurando os pinos
    gpio_init(button_A);//Inicializa o pino do botão A
    gpio_set_dir(button_A, GPIO_IN);// Configura o pino como entrada
    gpio_pull_up(button_A);// Habilita o pull-up interno
    gpio_init(button_B);//Inicializa o pino do botão B
    gpio_set_dir(button_B, GPIO_IN);// Configura o pino como entrada
    gpio_pull_up(button_B);// Habilita o pull-up interno
    gpio_init(LED_VERMELHO);// Inicializa o pino do LED vermelho
    gpio_set_dir(LED_VERMELHO, GPIO_OUT); // Configura o pino como saída  

    // Configuração da interrupção com callback
    gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled(button_B, GPIO_IRQ_EDGE_FALL,true);    
    while (true) {//No Loop é desenhado o número de acordo com o contador através de um vetor (numero[cont]) e é feito o LED vermelho piscar a cada 200ms(5Hz)
        desenho_pio(numero[cont], valor_led, pio, sm, intensidade * lista_de_cores[cor][0],//A cor do número é definido por outro contador (lista_de_cores[cor])
                                                    intensidade * lista_de_cores[cor][1] ,//As cores estão na ordem RGB
                                                    intensidade * lista_de_cores[cor][2]);//Além disso existe a váriavel intensidade que define o brilho
        gpio_put(LED_VERMELHO, true);
        sleep_ms(tempo);
        gpio_put(LED_VERMELHO, false);
        sleep_ms(tempo);
    }

}

void gpio_irq_handler(uint gpio, uint32_t events){
    uint32_t current_time = to_us_since_boot(get_absolute_time());// Obtém o tempo atual em microssegundos
    if (current_time - last_time > 200000){ // Verifica se passou tempo suficiente desde o último evento com 200 ms de debouncing 
        last_time = current_time; // Atualiza o tempo do último evento
        if(gpio == button_A){//Botão que decrementa o contador
            if(cont==0){
            cont = 9;
            }else{
            cont--;
            }
            if(cor==0){
            cor = 6;
            }else{
            cor--;
            }
            }
        else if(gpio == button_B){//Botão que incrementa o contador
            if(cont==9){
            cont = 0;
            }else{
            cont++;
            }
            if(cor==6){
            cor = 0;
            }else{
            cor++;
            }
        }
        printf("A = %d\n", cont);
        printf("B = %d\n", cor);
    }
}
