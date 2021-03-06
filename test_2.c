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

int main(int argc, char **argv)
{
     if (!bcm2835_init()){
          return 1;
     }
     else{
     inicjalizacja(PIN);
     }

//    [tutaj znajdzie się kod programu...]

    bcm2835_close();
}

unsigned char inicjalizacja(int pin)
{

int i, j, stat;
for(j=0;j<10;j++){
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP); //Ustawienie pinu jako wyjscie.
    STAN_NISKI(pin);  //Ustawienie magistrali w stan niski.
    delay(900);  //Odczekanie 500 milisekund.
    STAN_WYSOKI(pin);  //Zwolnienie magistrali.
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);  //Ustawienie pinu jako wejscie.
    bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_UP);

  for(i=1;i<51;i++){
  stat=bcm2835_gpio_lev(pin);
	if (stat==0)
	{
	printf("Próba %d.Odpowiedź DS18B20 przy %d-ej pętli.\n",j, i);
	}

  }
printf("\n");
}
printf("\n");



    return 0;
}

