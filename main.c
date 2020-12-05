#include <stdio.h>
#include "chiodolo.h"
#define MAX 30


/*
- spazio vuoto → 0
- muro → 1
- giocatore → 2
- uscita labirinto → 3
*/


int main() {
  //Carica la Mappa
  int a, b;
  char mappa[MAX][MAX];
  startScreen();
  generaMappa();
  FILE *input=NULL;
  input = fopen("map.txt", "r");
  for(a=0; a<MAX; a++){
    for(b=0; b<MAX; b++){
      mappa[a][b] = fgetc(input);
    }
    fseek(input, sizeof(char), SEEK_CUR);
  };
  //Stampa la Mappa
  for(a=0; a<MAX; a++){
    for(b=0; b<MAX; b++){
      if(mappa[a][b]=='1'){
        printf("# ");
      }else if(mappa[a][b]=='0'){
        printf("  ");
      }else if(mappa[a][b]=='2'){
        printf("L ");
      }else if(mappa[a][b]=='3'){
        printf("O ");
      }
    }
    printf("\n");
  }
  //cerco la posizione del giocatore e dell'uscita
  punto player, exit;
  for(a=0; a<MAX; a++){
    for(b=0; b<MAX; b++){
      if(mappa[a][b]=='2'){
        player.x = a;
        player.y = b;
      };
      if(mappa[a][b]=='3'){
        exit.x = a;
        exit.y = b;
      }
    }
  }
  punto movimento;
  //Cerca la mossa dell'utente
  sceltaMossa:
  printf("\n");
  char mossa;
  scanf("%c%*c", &mossa);
  switch(mossa){
    case 'w':
    case 'W':{//Mi muovo a N
      movimento.x = player.x - 1;
      movimento.y = player.y;
      if(mappa[movimento.x][movimento.y]=='3'){
        printf("Hai vinto\n");
        return 0;
      }else if (mappa[movimento.x][movimento.y]=='0'){
        mappa[player.x][player.y]='0';
        mappa[movimento.x][movimento.y]='2';
        player.x = movimento.x;
        player .y = movimento.y;
        for(a=0; a<MAX; a++){
          for(b=0; b<MAX; b++){
            if(mappa[a][b]=='1'){
              printf("# ");
            }else if(mappa[a][b]=='0'){
              printf("  ");
            }else if(mappa[a][b]=='2'){
              printf("L ");
            }else if(mappa[a][b]=='3'){
              printf("O ");
            }
          }
          printf("\n");
        }
      }
    }; break;
    case 'a':
    case 'A':{//Mi muovo a W
      movimento.x = player.x;
      movimento.y = player.y - 1;
      if(mappa[movimento.x][movimento.y]=='3'){
        printf("Hai vinto\n");
        return 0;
      }else if (mappa[movimento.x][movimento.y]=='0'){
        mappa[player.x][player.y]='0';
        mappa[movimento.x][movimento.y]='2';
        player.x = movimento.x;
        player .y = movimento.y;
        for(a=0; a<MAX; a++){
          for(b=0; b<MAX; b++){
            if(mappa[a][b]=='1'){
              printf("# ");
            }else if(mappa[a][b]=='0'){
              printf("  ");
            }else if(mappa[a][b]=='2'){
              printf("L ");
            }else if(mappa[a][b]=='3'){
              printf("O ");
            }
          }
          printf("\n");
        }
      }
    }; break;
    case 's':
    case 'S':{//Mi muovo a S
      movimento.x = player.x + 1;
      movimento.y = player.y;
      if(mappa[movimento.x][movimento.y]=='3'){
        printf("Hai vinto\n");
        return 0;
      }else if (mappa[movimento.x][movimento.y]=='0'){
        mappa[player.x][player.y]='0';
        mappa[movimento.x][movimento.y]='2';
        player.x = movimento.x;
        player .y = movimento.y;for(a=0; a<MAX; a++){
          for(b=0; b<MAX; b++){
            if(mappa[a][b]=='1'){
              printf("# ");
            }else if(mappa[a][b]=='0'){
              printf("  ");
            }else if(mappa[a][b]=='2'){
              printf("L ");
            }else if(mappa[a][b]=='3'){
              printf("O ");
            }
          }
          printf("\n");
        }
      }
    }; break;
    case 'd':
    case 'D':{//Mi muovo a E
      movimento.x = player.x;
      movimento.y = player.y + 1;
      if(mappa[movimento.x][movimento.y]=='3'){
        printf("Hai vinto\n");
        return 0;
      }else if (mappa[movimento.x][movimento.y]=='0'){
        mappa[player.x][player.y]='0';
        mappa[movimento.x][movimento.y]='2';
        player.x = movimento.x;
        player .y = movimento.y;
        for(a=0; a<MAX; a++){
          for(b=0; b<MAX; b++){
            if(mappa[a][b]=='1'){
              printf("# ");
            }else if(mappa[a][b]=='0'){
              printf("  ");
            }else if(mappa[a][b]=='2'){
              printf("L ");
            }else if(mappa[a][b]=='3'){
              printf("O ");
            }
          }
          printf("\n");
        }
      }
    }; break;
    case 'q':
    case 'Q':{
      printf("Esco dal gioco\n");
      return 0;
    }; break;
    default:{
      printf("Hai inserito un carattere sbagliato!!!\nInserirne uno nuovo\n");
    }
  }
  goto sceltaMossa;
  return 0;
}
