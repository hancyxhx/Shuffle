#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


struct {
    FILE *draw_deck;
} global_args;


void usage(){
    printf("Usage: shuffle [FILE]\n");
    printf("try `shuffle -h' for more information.\n");
    exit(-1);
}

void man(){
    printf("NAME\n");
    printf("\tshuffle - shuffle lines of text file\n");
    
    printf("SYNOPSIS\n");
    printf("\tshuffle [OPTION] [FILE]\n");

    printf("AUTHOR\n");
    printf("\tWritten by hancy hush\n");

    printf("REPORTING BUGS\n");
    printf("\tReport bugs to <hancyxhx@gmail.com>\n");
    
    exit(0);
}


void parse_arg(int argc, char *argv[]){
    /* set default value for global argument */
    global_args.draw_deck = stdin;

    /* read argument */
    int ch;
    while ((ch = getopt(argc, argv, "h")) != -1){
	switch (ch) {
	case 'h':
	    man();
	    break;
	case '?':
	defualt:
	    usage();
	    break;
	}
    }

    if(optind < argc - 1)
	usage();
    else if (optind == argc - 1){
	char *file = argv[optind];
	if ((global_args.draw_deck = fopen(file, "r")) == NULL){
	    fprintf(stderr, "ERROR: open %s\n", file);
	    exit(-1);
	}
    }
	
    return;
}


typedef char* Poker;
#define MAX_SHUFFLE_DECK_SIZE 1024 * 500

Poker draw(FILE *draw_deck){
    char* buf = NULL;
    size_t buf_len = 0;
    int bytes_read;

    bytes_read = getline(&buf, &buf_len, draw_deck);
    if(bytes_read == -1)
	return NULL;
    else{
	Poker poker = malloc(bytes_read);
	strcpy(poker, buf);
	return poker;
    }
}


Poker* shuffle(FILE *draw_deck){
    int i;
    srand( (unsigned int)time(NULL) );
    Poker *shuffle_deck = malloc(sizeof(Poker) * MAX_SHUFFLE_DECK_SIZE);
    for (i = 0; i < MAX_SHUFFLE_DECK_SIZE; i++)
	shuffle_deck[i] = NULL;
	
    int pokercnt=0;
    Poker crrnt_poker;
    while ( (crrnt_poker = draw(draw_deck)) != NULL){
    	pokercnt++;

    	int insert_position = rand() % pokercnt;
    	if (insert_position != pokercnt -1)
    	    shuffle_deck[pokercnt - 1] = shuffle_deck[insert_position];
    	shuffle_deck[insert_position] = crrnt_poker;
    }
    return shuffle_deck;
}


void show_deck(Poker deck[]){
    int i;
    for (i=0; deck[i] != NULL; i++)
	printf("%s",deck[i]);
}


int main (int argc, char *argv[] ){
    parse_arg(argc, argv);

    Poker *shuffle_deck;
    shuffle_deck = shuffle(global_args.draw_deck);

    show_deck(shuffle_deck);

    return 0;
}
