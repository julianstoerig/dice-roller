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

void
usage(FILE* f)
{
	fprintf(f, "Usage:\n");
	fprintf(f, "    dice        to roll 1d6\n");
	fprintf(f, "    dice n      to roll nd6\n");
	fprintf(f, "    dice n k    to roll ndk\n");
}


int
main(int argc, char** argv)
{
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
				usage(stderr);
				exit(1);
			}
		}
	}
	else
	{
		assert(false && "argument count should be 3 at this point");
	}

	for (i32 i=0; i<n; i+=1)
	{
		i32 roll = rand() % k + 1;
		if (i > 0)
		{
			fprintf(stdout, " ");
		}
		fprintf(stdout, "%d", roll);
	}
	fprintf(stdout, "\n");
}
