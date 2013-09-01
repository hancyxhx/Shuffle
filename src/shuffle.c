#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


#define MAX_SHUFFLE_DECK_SIZE 1024 * 500
typedef char* Poker;


Poker draw(FILE *draw_deck){
    char* buf = NULL;
    int buf_len = 0;
    int bytes_read;

    bytes_read = getline(&buf, &buf_len, draw_deck);
    if(bytes_read == -1)
	return NULL;
    else{
	char *poker = malloc(bytes_read + 1);
	strcpy(poker, buf);
	return poker;
    }
}

void show_deck(Poker deck[]){
    int i;
    for (i=0; deck[i] != NULL; i++){
	printf("%d", atoi(deck[i]));
	printf("%c", (deck[i + 1] != NULL) ? ' ' : '\n');
    }
}


struct {
    FILE *draw_deck;
    Poker *shuffle_deck;
} global_args;

void usage(){
    printf("Usage: shuffle [-f file]\n");
    exit(-1);
}

void parse_arg(int argc, char *argv[]){
    /* set default value for global argument */
    global_args.draw_deck = stdin;
    global_args.shuffle_deck = malloc(sizeof(Poker) * MAX_SHUFFLE_DECK_SIZE);

    /* read argument */
    int ch;
    while ((ch = getopt(argc, argv, "f:h")) != -1){
	switch (ch) {
	case 'f':
	    if ((global_args.draw_deck = fopen(optarg, "r")) == NULL){
		fprintf(stderr, "EROOR: open %s\n", optarg);
		exit(-1);
	    }
	    break;
	case 'h':
	    usage();
	    break;
	case '?':
	defualt:
	    usage();
	    break;
	}
    }

    return;
}




int main (int argc, char *argv[] ){
    parse_arg(argc, argv);

    srand( (unsigned int)time(NULL) );
    int pokercnt=0;
    Poker crrnt_poker;
    while ( (crrnt_poker = draw(global_args.draw_deck)) != NULL){
    	pokercnt++;

    	int insert_position = rand() % pokercnt;
    	if (insert_position != pokercnt -1)
    	    global_args.shuffle_deck[pokercnt - 1] = global_args.shuffle_deck[insert_position];
    	global_args.shuffle_deck[insert_position] = crrnt_poker;
    }

    show_deck(global_args.shuffle_deck);

    return 0;
}
