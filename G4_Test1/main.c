#include "RTE_Components.h"
#include CMSIS_device_header

//macro para generar la mascara de un bit
#define MASK(x) (1 << (x))

/* Pines de los pulsadores entradas (todos en CN4) */
#define Pin_Boton1  0   /* PB0 */
#define Pin_Boton2  4   /* PB4 */
#define Pin_Boton3  5   /* PB5 */
#define Pin_Boton4  6   /* PB6 */
#define Pin_Boton5  8   /* PA8 */

/* Pines de los LEDs salidas (todos en CN3) */
#define Pin_LED1    1   /* PA1 */
#define Pin_LED2    0   /* PA0 */
#define Pin_LED3    4   /* PA4 */
#define Pin_LED4    5   /* PA5 */
#define Pin_LED5    6   /* PA6 */




int main() {

    // habilitar el reloj de los puertos A y B
    RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;
    RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    //botoness como entrada 00
    //& para apagar los bits de la posicion del pin y dejarlo en 00
    GPIOB -> MODER &= ~(MASK(2*Pin_Boton1) | MASK(2*Pin_Boton1+1));
    GPIOB -> MODER &= ~(MASK(2*Pin_Boton2) | MASK(2*Pin_Boton2+1));
    GPIOB -> MODER &= ~(MASK(2*Pin_Boton3) | MASK(2*Pin_Boton3+1));
    GPIOB -> MODER &= ~(MASK(2*Pin_Boton4) | MASK(2*Pin_Boton4+1));
    GPIOA -> MODER &= ~(MASK(2*Pin_Boton5) | MASK(2*Pin_Boton5+1));

    //Leds como salida 01
    //& para limpiar ambos bits de la posicion del pin y dejarlos en 00
    //| para poner en 01 el bit de la posicion del pin
    GPIOA -> MODER &= ~(MASK(2*Pin_LED1) | MASK(2*Pin_LED1+1));
    GPIOA -> MODER |= MASK(2*Pin_LED1);

    GPIOA -> MODER &= ~(MASK(2*Pin_LED2) | MASK(2*Pin_LED2+1));
    GPIOA -> MODER |= MASK(2*Pin_LED2);

    GPIOA -> MODER &= ~(MASK(2*Pin_LED3) | MASK(2*Pin_LED3+1));
    GPIOA -> MODER |= MASK(2*Pin_LED3);

    GPIOA -> MODER &= ~(MASK(2*Pin_LED4) | MASK(2*Pin_LED4+1));
    GPIOA -> MODER |= MASK(2*Pin_LED4);

    GPIOA -> MODER &= ~(MASK(2*Pin_LED5) | MASK(2*Pin_LED5+1));
    GPIOA -> MODER |= MASK(2*Pin_LED5);

    //habilitar pull-down 10
    //& para limpiar ambos bits de la posicion del pin y dejarlos en 00
    //| para poner en 10 el bit de la posicion del pin
    //lo de pull down solo tiene sentido en registros de entrada, por eso se hace solo para los botones
    GPIOB -> PUPDR &= ~(MASK(2*Pin_Boton1) | MASK(2*Pin_Boton1+1));
    GPIOB -> PUPDR |= MASK(2*Pin_Boton1+1);

    GPIOB -> PUPDR &= ~(MASK(2*Pin_Boton2) | MASK(2*Pin_Boton2+1));
    GPIOB -> PUPDR |= MASK(2*Pin_Boton2+1);

    GPIOB -> PUPDR &= ~(MASK(2*Pin_Boton3) | MASK(2*Pin_Boton3+1));
    GPIOB -> PUPDR |= MASK(2*Pin_Boton3+1);

    GPIOB -> PUPDR &= ~(MASK(2*Pin_Boton4) | MASK(2*Pin_Boton4+1));
    GPIOB -> PUPDR |= MASK(2*Pin_Boton4+1);

    GPIOA -> PUPDR &= ~(MASK(2*Pin_Boton5) | MASK(2*Pin_Boton5+1));
    GPIOA -> PUPDR |= MASK(2*Pin_Boton5+1);

    while (1){

        //si el boton esta presionado, se enciende el led correspondiente
        //IDR input data register, ODR output data register
        //lee IDR y si el bit correspondiente al pin del boton es 1, enciende el led correspondiente, sino lo apaga
        if(GPIOB -> IDR & MASK(Pin_Boton1)){
            GPIOA -> ODR |= MASK(Pin_LED1);
        } else {
            GPIOA -> ODR &= ~MASK(Pin_LED1);
        }

        //boton 2
        if(GPIOB->IDR & MASK(Pin_Boton2)){
            GPIOA -> ODR |= MASK(Pin_LED2);
        }else {
            GPIOA -> ODR &= ~MASK(Pin_LED2);
        }

        //boton 3
        if(GPIOB->IDR & MASK(Pin_Boton3)){
            GPIOA -> ODR |= MASK(Pin_LED3);
        }else {
            GPIOA -> ODR &= ~MASK(Pin_LED3);
        }

        //boton 4
        if(GPIOB->IDR & MASK(Pin_Boton4)){
            GPIOA -> ODR |= MASK(Pin_LED4);
        }else {
            GPIOA -> ODR &= ~MASK(Pin_LED4);
        }

        //boton 5
        if(GPIOA->IDR & MASK(Pin_Boton5)){
            GPIOA -> ODR |= MASK(Pin_LED5);
        }else {
            GPIOA -> ODR &= ~MASK(Pin_LED5);
        }

        
        // GPIOA->ODR &= ~(MASK(Pin_LED1) | MASK(Pin_LED2) | MASK(Pin_LED3) | MASK(Pin_LED4) | MASK(Pin_LED5));

        // if (GPIOB->IDR & MASK(Pin_Boton1))
        //     GPIOA->ODR |= MASK(Pin_LED1);
        // else if (GPIOB->IDR & MASK(Pin_Boton2))
        //     GPIOA->ODR |= MASK(Pin_LED2);
        // else if (GPIOB->IDR & MASK(Pin_Boton3))
        //     GPIOA->ODR |= MASK(Pin_LED3);
        // else if (GPIOB->IDR & MASK(Pin_Boton4))
        //     GPIOA->ODR |= MASK(Pin_LED4);
        // else if (GPIOA->IDR & MASK(Pin_Boton5))
        //     GPIOA->ODR |= MASK(Pin_LED5);
        

    }

}
