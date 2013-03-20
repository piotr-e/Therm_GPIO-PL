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
unsigned char inicjalizacja();
void zapisz_bit(char bit);
unsigned char odczytaj_bit(void);

int main(int argc, char **argv)
{
     if (!bcm2835_init()){
          return 1;
     }
     else{
     inicjalizacja();
     }

//    [tutaj znajdzie się kod programu...]

    bcm2835_close();
}


unsigned char inicjalizacja() 
{
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP); //Ustawienie pinu jako wyjscie.
    STAN_NISKI(PIN);  //Ustawienie magistrali w stan niski.
    delay(100);  //Odczekanie 500 milisekund.
    STAN_WYSOKI(PIN);  //Zwolnienie magistrali.
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);  //Ustawienie pinu jako wejscie.
    bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);

    int stat;
    stat = bcm2835_gpio_lev(PIN);
    int i;
    for(i=0;i<40;i++){
    if (stat==0)
        {
        printf("DS18B20 zglosil swoja obecnosc, oczekiwanie %d. \n", i);
        }
	stat = bcm2835_gpio_lev(PIN);
    }
    if (stat==1)
       {
       printf("Magistrala gotowa do komunikacji.\n");
       }

    return 0;
}

void zapisz_bit(char bit){
  STAN_NISKI(PIN);
    delay(5);
    if(bit==1){
	STAN_WYSOKI(PIN);
	}
	else{
	delay(80);
	STAN_WYSOKI(PIN);
	}
//return 0;
}

unsigned char odczytaj_bit(void){
  unsigned char ustawiony_bit = 0;
  STAN_NISKI(PIN);
  delay(2);
  STAN_WYSOKI(PIN);
  delay(15);
  bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);  //Ustawienie pinu jako w$
  bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);

  int stat;
  stat = bcm2835_gpio_lev(PIN);
  if (stat==1)
        {
        ustawiony_bit=1;
        }
        else
        {
        ustawiony_bit=0;
        }

return(ustawiony_bit);
}


void zapisz_bajt(char bajt_danych){
  unsigned char i, pom;
  for(i=0;i<8;i++){
    pom=bajt_danych>>i;
    pom&=0x01;
    zapisz_bit(pom);
  }
delay(100);
//return 0;
}


unsigned char odczytaj_bajt(void){
  unsigned char bajt_danych, i;
  for(i=0;i<8;i++){
   if(odczytaj_bit()) bajt_danych|=0x01<<i;
   delay(15);
  }
return(bajt_danych);
}

