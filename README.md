# Display numérico em uma matriz de LEDs acionado através de botões
Este projeto tem como objetivo verificar e testar o funcionamento de interrupção através do acionamento de botões em um Raspberry Pi Pico W. 
No qual será alterado os números mostrados em uma matriz de LEDs WS2812 através de comandos obtidos via os botões.

# Como baixar e executar o código
    1-Baixar ou utilizar git clone no repositório.
          git clone https://github.com/MSoares0079/EmbarcaTech_Display_numerico_interrupcao.git
    2-Ter o VS Code instalado e devidamente configurado.
    3-Ter a extensão do Raspberry Pi Pico instalada no VS Code.
    4-Compilar o arquivo "Display_numerico_na_matriz_de_LEDs_INTERRUPCAO.c" utilizando o compilador do Raspberry Pi Pico.
    5-O código pode ser simulado pelo "diagram.json" apartir da extensão Wokwi,
      caso deseje compilar em um Pi Pico W é necessário identificar os pinos atribuidos aos botões e a matriz de LED,
      para compilar especificamente na placa disponibilizado pelo EmbarcaTech não é necessário alterações no hardware.

# Estrutura do código

O algoritmo é tem apenas a rotina da função principal(int main) no qual é acionado um LED vermelho na frequência de 5Hz, 
porém existe na matriz de LEDs WS2812 um número que está sendo mostrado, inicialmente o número 0, 
em que apartir dos botões A e B, da placa da BitDogLab disponibilizada pelo EmbarcaTech, esse número é alterado. 

O botão A decrementa esse número enquanto o botão B incrementa, essas ações de apertar o botão, ou eventos, são tratados como interrupção pelo sistema.
No qual o programa sai da rotina da função principal e trata a interrupção, que significa executar determinada ação.

A ação escolhida para é alterar o valor de dois contadores: 
"cont" que decide qual o número será mostrado na matriz de LEDs e "cor" que define a cor do número.

# Video demonstrando o funcionamento do código

https://drive.google.com/file/d/1cBuRslo6GWgN-DS8gf2o-E460QMwtCfH/view?usp=sharing
