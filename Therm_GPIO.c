/*
 * PL:
 * Sterownik dla urzadzen - DS18B20.    
 * Podlaczonych do pinów GPIO.
 *
 * EN:
 * Driver for devices - DS18D20.
 * Connected to GPIO pins.
 *
 */
 
#include <bcm2835.h>  //To jest właśnie plik nagłówkowy naszej biblioteki GPIO. It is header file our GPIO library. 
#include <stdio.h>

#define PIN RPI_V2_GPIO_P5_06  //To jest GPIO31. It is GPIO31.

#define STAN_NISKI(g) bcm2835_gpio_write(g, LOW);  //to makro ustawia stan niski
#define STAN_WYSOKI(g) bcm2835_gpio_write(g, HIGH);  //to makro ustawia stan wysoki

int g;  //Zmienna pinu GPIO.
char buf[8];  //Zmienna potrzebna do konwersji temperatury.
unsigned char inicjalizacja(int pin);
