#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "rnd_rng.c"
#include "str_compare.c"


/*
 * FEEDBACK FROM PETE 26/07/2020
 * FIXED 1) sleep_delay = char_count / 10 is producing zero
 * FIXED 2) Usleep might be better as it does microseconds. Need to then convert everything to microseconds to use it.
 * FIXED 3) Make division by 10 a double and cast character_count as a double
 * ASK ABOUT THIS 4) functionize some of the code. Rule of thumb is you should be able to describe its function within 1 sentence. Main should really only be calling other functions.
 * Functionizing can make it easier to debug as its easier to find when something isn't going right.
 * 5) use the 'man' function in linux for checking stuff (including stuff in c). e.g. man ls or something like that. May need to use man1, man2, etc. to get the right command.
 * 6) keep track of how long buffers are?
 * 7) shouldn't ever really include c files. You should use an h.file instead. h files are the same as c files, but conventionally we only include h.files.
 * FIXED 8) printf tries to manage the way you interact with thh kernel to minimize the syscalls. So instead of sending things piece by piece it buffers it up and sends it all at once. This is creating issues.
 * Using fflush here can help. Look at the example people sent.
 * 9) Writing empty loops to clear the buffer is not the best way. But it's fine here.
 * 10) Keep an eye on indentation. Reasonable.
 * 11) Pete suggested writing a mandelbrought generator. Something that generates an image file.
 */

int main(int argc, char *argv[])
{
    char input[] = "play";
    int c;
    int seed_time;
    char rules = 'x'; /* not certain why I had difficulties using fgets with a char here - fgets subtracts 1 from array length */

    /* game variables */
    int level = 1;
    int flag = 1;
    char letters[100];
    char guess[100];
    int char_count = 4;
    double sleep_delay = 1000000;
    int score = 0;

    while(!str_compare(sizeof(input), input, "exit"))
    {

        puts("Welcome to Clefairy Says 2.0! Type 'play' to begin a game or 'exit' to quit.");
        fgets(input, sizeof(input), stdin);

        /* get char reads a character from standard input. Here it's just reading to absorb the new line character left in the buffer. 
        Removed && != EOF as not relevant here  */
        while((c = getchar()) != '\n')
        {
            ;
        }

        /* This is the core part of the game */
        if(str_compare(sizeof(input), input, "play"))
        {
		/* rules check */
		puts("Do you know the rules? (y/n)");
		while(rules != 'y' && rules != 'n')
		{
			fgets(&rules, sizeof(rules) + 1, stdin); /* Added 1 to sizeof to account for fgets subtracting 1 for use with arrays that inc null terminating char */
			while((c = getchar()) != '\n')
			{
				;
			}
			
			if(rules != 'y' && rules != 'n')
			{
				puts("Please input 'y' for yes or 'n' for no");
			}
		}

		while(rules != 'y')
		{
            		puts("The rules of Clefairy Says are simple. Over a 10 second interval a number of letters will appear on the screen separated by spaces. Once the pattern is finished, the screen will be wiped and the player will have to input the pattern from memory (don't include spaces). If correct, they gain points equal to the number of correct characters then move up a level. Each successive level will increase in difficulty by repeating the pattern with an increasing number of characters.");
			puts("Press any key to begin");
			fgets(&rules, sizeof(rules) + 1, stdin);
			rules = 'y';
		}

	    /* resetting for a new game */
	    /* set the seed time out here and run it in the loop so we don't need to store the randomnly generated characters, we can just regenerate them from same seed */
	    seed_time = time(NULL);
	    flag = 1;
	    score = 0;

	    /* this is the core game loop - this will repeat until the player loses the game */
	    while(flag)
	    {
		    /* increment level */
		    level++;
		    
		    /* updating character counter */
		    char_count = 2 * level + 4;
		    /* reusing the seed */
		    seed(seed_time);
		    /* 10 second delay spread across the total character count. This should make it more difficult as count increases */
		    sleep_delay = 10000000 / char_count;

		    printf("***LEVEL %i***\n", level);
	
		    /* delay before level starts */
		    usleep(1000000);

		    for(int i = 0; i < (char_count); i++)
		    {
			    letters[i] = rnd_char();	    
			    printf("%c ", letters[i]);
			    fflush(stdout);
			    usleep(sleep_delay);
		    }

		    for(int i = 0; i < 100; i++)
		    {
			    puts("\n");
		    }

		    puts("Please input the pattern: ");
		    fgets(guess, char_count + 1, stdin);
		    while((c = getchar()) != '\n')
		    {
			    ;
		    }

		    for(int i = 0; i < char_count; i++)
		    {
			if(letters[i] == guess[i])
			{
				score++;
				continue;
			}
			else
			{
				printf("Incorrect guess. You guessed: %c, the correct guess was %c\n", guess[i], letters[i]);
				flag = 0;
			}
		    }
	    }
	    printf("You got to level %i, with a score of %i\n", level, score);
	    rules = 'x'; /* reset rules */
	    puts("\n\n");
        }

    }

    return 0;
}
