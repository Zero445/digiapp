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
#define CUR_W_NUM	8

typedef struct
{
	int	size;
	char	chrs[WORD_MAX_SIZE];
} word_t;


typedef struct
{
	bool	playing;
	int	current_word;
	int	current_chr;
	int	remaining_chances;
	int	chr;
	int score;


} state_t ;


char	word_list[WORD_MAX_COUNT][WORD_MAX_SIZE] = {"malicia", "mizeria", "fluxo", "constante", "anime", "visual", "rock", "gotico"};


word_t	words[WORD_MAX_COUNT] = {0};

int score;

int win_x, win_y;


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
		mvprintw(y/2, init_x+i,"%c",word->chrs[i]);
	}

}

void GameUpdateRender(state_t	*game_state)
{
	if (game_state->playing == false)
	{
		game_state->current_word = random() % CUR_W_NUM;
		game_state->remaining_chances = 3;
		game_state->playing = true;
		game_state->current_chr = 0;
		game_state->chr = 0;
	}
	else
	{
		if (game_state->remaining_chances > 0 && game_state->current_chr < words[game_state->current_word].size)
		{
			// RENDER START
			
			clear();

			mvprintw(2,2,"%d",game_state->score);
			put_word(win_y/2,(win_x/2)-words[game_state->current_word].size/2,&(words[game_state->current_word]));
			


			// RENDER END
			game_state->chr = getch();
			if (game_state->chr == words[game_state->current_word].chrs[game_state->current_chr])
			{
				game_state->current_chr += 1;

			}
			else
			{
				game_state->remaining_chances -= 1;
				game_state->current_chr = 0;
			}
		}	
		else
		{
			game_state->playing = false;
			if (game_state->current_chr == words[game_state->current_word].size)
			{
				game_state->score += 100;
			}
			else
			{
				game_state->score -= 1;
			}
		}
	}

}

int main(int argc, char *argv[])
{

	state_t		game_state = { .playing = false, 0};
	struct tm	time;
	bool	should_close = 0;


	mktime(&time);
	srandom(time.tm_year * time.tm_sec + 2);
	generate_words();




	initscr();
	cbreak();
	noecho();
	keypad(stdscr,TRUE);

	while(!should_close)
	{	
		getmaxyx(stdscr, win_y, win_x);
		if (game_state.chr == 27)
		{
			should_close = 1;
		}




		if (win_x < min_x || win_y < min_y)
		{
			mvprintw(win_y/2, win_x/2, "Window too small!");
		}
		else
		{
			GameUpdateRender(&game_state);
		}	


	}
	endwin();
	return 0;
}

