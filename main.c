#include "stdio.h"
#include "stdlib.h"
#include "ncurses.h"
#include "stdbool.h"
#include "string.h"
#include "time.h"


#define min_x	40
#define min_y	20
#define WORD_MAX_SIZE 21
#define WORD_MAX_COUNT	255	

typedef struct
{
	int	size;
	char	chrs[WORD_MAX_SIZE];
} word_t;



char	word_list[WORD_MAX_COUNT][WORD_MAX_SIZE] = {"Malicia", "Mizeria", "Fluxo", "Constante", "Anime", "Visual", "Rock", "Gotico"};


word_t	words[WORD_MAX_COUNT] = {0};





void generate_words()
{
	for (int i=0; i < WORD_MAX_COUNT; ++i)
	{
		words[i].size = strlen(word_list[i]);
		strcpy(words[i].chrs, word_list[i]);
	}
}

void put_word(int y, int init_x, word_t *word)
{
	for (int i=0; i < word->size; ++i)
	{
		mvprintw(y, init_x+i,"%c",word->chrs[i]);
	}

}


int main(int argc, char *argv[])
{

	struct tm time;
	mktime(&time);
	srandom(time.tm_year * time.tm_sec + 2);
	generate_words();

	int ch;
	int win_x, win_y;
	bool	should_close = 0;
	initscr();
	cbreak();
	noecho();
	keypad(stdscr,TRUE);
	
	while(!should_close)
	{	
		getmaxyx(stdscr, win_y, win_x);
		int random_word = random() % 8 ;
		ch = getch();
		
		if (ch == 27)
		{
			should_close = 1;
		}
		
		clear();	
		
		
		
		if (win_x < min_x || win_y < min_y)
		{
			mvprintw(win_y/2, win_x/2, "Window too small!");
		}
		else
		{
			put_word(win_y/2,win_x/2,&(words[random_word]));
		}	
		
		
		refresh();
	}
	endwin();
	return 0;
}

