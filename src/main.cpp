#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>

typedef uint32_t u32;
typedef  int32_t i32;

const char *rank_strs[] = {
	"2", "3", "4", "5", "6", "7", "8", "9", "10",
	"Jack", "Queen", "King", "Ace",
};
const char *suit_strs[] = {
	"Hearts",
	"Diamonds",
	"Clubs",
	"Spades",
};


void
usage(FILE* f)
{
	fprintf(f, "Usage:\n");
	fprintf(f, "    dice        to roll 1d6\n");
	fprintf(f, "    dice n      to roll nd6\n");
	fprintf(f, "    dice n k    to roll ndk\n");
	fprintf(f, "    dice n card to roll n cards, with replacement\n");
}


int
main(int argc, char** argv)
{
    u32 draw_cards = 0;
	i32 n = 0;
	i32 k = 0;

	struct timespec ts = {};
	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
	srand(ts.tv_nsec * getpid());
	
	if (argc > 3)
	{
		usage(stderr);
		exit(1);
	}
	else
	if (argc == 1)
	{
		n = 1;
		k = 6;
	}
	else
	if (argc == 2)
	{
		const char* help_str_long = "--help";
		const char* help_str_shrt = "-h";
		if ((strncmp(argv[1], help_str_long, strlen(help_str_long)) == 0) || (strncmp(argv[1], help_str_shrt, strlen(help_str_shrt)) == 0))
		{
			usage(stdout);
		}
		else
		{
			char* valid = NULL;

			n = strtol(argv[1], &valid, 10);
			k = 6;

			if (valid == argv[1])
			{
				usage(stderr);
				exit(1);
			}
		}
	}
	else
	if (argc == 3)
	{
		const char* help_str_long = "--help";
		const char* help_str_shrt = "-h";
		if ((strncmp(argv[1], help_str_long, strlen(help_str_long)) == 0) || (strncmp(argv[1], help_str_shrt, strlen(help_str_shrt)) == 0))
		{
			usage(stdout);
		}
		else
		{
			char* valid_n = NULL;
			char* valid_k = NULL;
			n = strtol(argv[1], &valid_n, 10);
			k = strtol(argv[2], &valid_k, 10);

			if (valid_n == argv[1])
			{
				usage(stderr);
				exit(1);
			}
			if (valid_k == argv[2])
			{
				const char* card_str = "card";
				if (strncmp(argv[2], card_str, strlen(card_str)) == 0)
				{
					draw_cards = 1;
				}
				else
				{
					usage(stderr);
					exit(1);
				}
			}
		}
	}
	else
	{
		assert(false && "argument count should be 3 at this point");
	}
	for (i32 i=0; i<n; i+=1)
	{
		if (draw_cards)
		{
			i32 suit = rand() % 4;
			i32 rank = rand() % 11;
			if (i > 0)
			{
				fprintf(stdout, ", ");
			}
			fprintf(stdout, "%s of %s", rank_strs[rank], suit_strs[suit]);
		}
		else
		{
			i32 roll = rand() % k + 1;
			if (i > 0)
			{
				fprintf(stdout, " ");
			}
			fprintf(stdout, "%d", roll);
		}
	}
	fprintf(stdout, "\n");
}
