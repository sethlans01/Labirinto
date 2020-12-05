#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chiodolo.h"

void trattino(){
  int i=0;
  for(i; i<167; i++){
    printf("-");
  }
  printf("\n");
}

void startScreen(){
  trattino();
  printf("        ___\n");
  printf("      _/ @@\\        OH NO!\n");
  printf("     ( \\  O/__ \n");
  printf("      \\    \\__)     Lalla.exe si è persa in un labirinto...\n");
  printf("      /     \\       Aiutala ad uscire.\n");
  printf("     /      _\\\n");
  printf("    `\"\"\"\"\"``\n");
  trattino();
  printf("\n\nISTRUZIONI:\nUsare WASD per muoversi\nPremere Q per terminare il gioco\n");
}

void generaMappa(){
  int mappa[20][20], contatoreA, contatoreB, *map=NULL;
  map = &mappa[0][0];
  /*
  - spazio vuoto → 0
  - muro → 1
  - giocatore → 2
  - uscita labirinto → 3
  */
  //Inizializzo la mappa come una matrice composta solamente da muri
  for(contatoreA=0; contatoreA<20; contatoreA++){
    for(contatoreB=0; contatoreB<20; contatoreB++){
      mappa[contatoreA][contatoreB] = 1;
    }
  }
  //Array per vedere se sono già passato in alcune coordinate
  punto giapassato[70], *puntagiapassato=NULL;
  int puntipassati = 0;
  puntagiapassato = &giapassato[0];
  //Inizio a scavare il tunnel
  punto corrente, *punt=NULL;
  mappa[10][10] = 0;
  corrente.x = 10;
  corrente.y = 10;
  punt = &corrente;
  do{
    punto fittizio;
    fittizio = randomico(punt, puntagiapassato);
    mappa[fittizio.x][fittizio.y] = 0;
    if(fittizio.x<corrente.x){//scavo a N
      mappa[(fittizio.x)+1][fittizio.y] = 0;
    }else if(fittizio.y>corrente.y){// scavo a E
      mappa[corrente.x][(corrente.y)+1] = 0;
    }else if(fittizio.x>corrente.x){// scavo a S
      mappa[(fittizio.x)-1][fittizio.y] = 0;
    }else if(fittizio.y<corrente.y){// scavo a W
      mappa[corrente.x][(corrente.y)-1] = 0;
    };
    giapassato[puntipassati].x = fittizio.x;
    giapassato[puntipassati].y = fittizio.y;
    puntipassati++;
    corrente.x = fittizio.x;
    corrente.y = fittizio.y;
  }while(puntipassati<70);
  //

  int a=0, b=0;
  for(a=0; a<20; a++){
    for(b=0; b<20; b++){
      if(mappa[a][b]==1){
        printf("# ");
      }else{
        printf("  ");
      }
    }
    printf("\n");
  }

};

punto randomico(punto *p, punto *gia){
  srand(time(NULL));
  //coordinate dei punti adiacenti a punto corrente
  punto nord, est, sud, ovest, random, *puntaRandom=NULL;
  puntaRandom = &random;
  nord.x = p->x-2;
  est.x = p->x;
  sud.x = p->x+2;
  ovest.x = p->x;
  nord.y = p->y;
  est.y = p->y+2;
  sud.y = p->y;
  ovest.y = p->y-2;
  ciao:
  {
  //scelgo casualmente uno dei punti adiacenti a punto corrente
  int casuale;
  casuale = rand()%4 +1;
  switch(casuale){
    case 1:{
      random.x = nord.x;
      random.y = nord.y;
    }; break;
    case 2:{
      random.x = est.x;
      random.y = est.y;
    }; break;
    case 3:{
      random.x = sud.x;
      random.y = sud.y;
    }; break;
    case 4:{
      random.x = ovest.x;
      random.y = ovest.y;
    }; break;
  };
  //verifico che punto random sia valido (non deve essere un muro del bordo)
  bool valido;
  valido = puntoValido(puntaRandom, gia);
  bool nuovo;
  nuovo = puntoNuovo(puntaRandom, gia);
  if(valido&&nuovo){
    return random;
  }else{
    goto ciao;
  }
}
};

bool puntoValido(punto *p, punto *gia){
  bool a = true;
  if(p->x<1||p->x>18||p->y<1||p->y>18){
    a = false;
  };
  return a;
};

bool puntoNuovo(punto *p, punto *gia){
  bool a;
  int i=0;
  for(i; i<70; i++){
    if(p->x==gia[i].x&&p->y==gia[i].y){
      return false;
    };
  }
  return true;
};
