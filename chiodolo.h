#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
  int x;
  int y;
}punto;

typedef enum{false, true} bool;

void startScreen();
void trattino();
void generaMappa();
punto randomico(punto *p, punto *gia);
bool puntoValido(punto *p, punto *gia);
bool puntoNuovo(punto *p, punto *gia);
