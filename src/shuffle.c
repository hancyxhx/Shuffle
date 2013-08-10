#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define DRAW_DECK stdin
#define MAX_SHUFFLE_DECK_SIZE 1024 * 500

typedef char* Poker;

Poker draw(FILE *draw_deck){
  Poker pk = malloc(1024);
  return (fgets(pk, 1024, draw_deck) != NULL) ? pk : NULL;
}

void show_deck(Poker deck[]){
  int i;
  for (i=0; deck[i] != NULL; i++){
    printf("%d", atoi(deck[i]));
    printf("%c", (deck[i + 1] != NULL) ? ' ' : '\n');
  }
}

Poker shuffle_deck[MAX_SHUFFLE_DECK_SIZE];
int main (int argc, char *argv[] ){
  srand( (unsigned int)time(NULL) );

  int pokercnt=0;
  Poker crrnt_poker;
  while ( (crrnt_poker = draw(DRAW_DECK)) != NULL){
    pokercnt++;

    int insert_position = rand() % pokercnt;
    if (insert_position != pokercnt -1)
      shuffle_deck[pokercnt - 1] = shuffle_deck[insert_position];
    shuffle_deck[insert_position] = crrnt_poker;
  }

  show_deck(shuffle_deck);

  return 0;
}
