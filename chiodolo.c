#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chiodolo.h"
#define MAX 30

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
  printf("\n\nISTRUZIONI:\nUsare WASD per muoversi\nPremere Q per terminare il gioco\n\n\n");
}

void generaMappa(){
  srand(time(NULL));
  int mappa[MAX][MAX], *map=NULL;
  int a=0, b=0, temp;
  map = &mappa[0][0];
  //Inizializzo la mappa come una matrice composta solamente da muri
  for(a=0; a<MAX; a++){
    for(b=0; b<MAX; b++){
      mappa[a][b] = 1;
    };
  };
  //Array per vedere se sono già passato in alcune coordinate
  punto giapassato[70], *puntagiapassato=NULL;
  int puntipassati = 0;
  puntagiapassato = &giapassato[0];
  //Inizio a scavare il tunnel
  punto corrente, *punt=NULL;
  mappa[MAX/2][MAX/2] = 0;
  corrente.x = MAX/2;
  corrente.y = MAX/2;
  punt = &corrente;
  do{
    punto fittizio;
    fittizio = randomico(punt, puntagiapassato);
    temp = fittizio.x;
    if(temp!=-1){
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
    } else {
      goto fanculo;
    }
  }while(puntipassati<70);
  fanculo:{
  //genero il giocatore
  int plX, plY;
  giocatorre:
  plX = rand()%31;
  plY = rand()%31;
  if(mappa[plX][plY]==0){
    mappa[plX][plY] = 2;
  } else{
    goto giocatorre;
  }
  //genero l'ucita
  mappa[MAX/2][MAX/2] = 3;
  //salvo la mappa in un file
  FILE *output=NULL;
  output = fopen("map.txt", "w");
  for(a=0; a<MAX; a++){
    for(b=0; b<MAX; b++){
      fprintf(output, "%d", mappa[a][b]);
    };
    fprintf(output, "\n");
  };
  fclose(output);
}
};

punto randomico(punto *p, punto *gia){
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
  int direzioni[4]={0,0,0,0};  //N-E-S-W
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
    direzioni[casuale-1] = 1;
    if(direzioni[0]==0||direzioni[1]==0||direzioni[2]==0||direzioni[3]==0){
      goto ciao;
    }else{
      random.x = -1; //valore a caso che non è minore del limite della mappa
      return random;
    };
  };
  }
};

bool puntoValido(punto *p, punto *gia){
  bool a = true;
  if(p->x<1||p->x>(MAX-2)||p->y<1||p->y>(MAX-2)){
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
