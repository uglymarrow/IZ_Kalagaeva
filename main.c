
#include <stdio.h>
#include <stdlib.h>

#include "server.h"

int main()
{
	server *servers = NULL;
	size_t count = 0;
	unsigned char input_continues = 1;

	printf("Input servers data \n");
	do
	{
		count++;
		servers = (server *)realloc(servers, sizeof(server) * count);

		if (! servers)
		{
			fprintf(stderr, "%s", "Failed to allocate memory \n");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (input_server_data(servers, count) != EXIT_SUCCESS)
			{
				fprintf(stderr, "%s", "Failed to input server data \n");
				exit(EXIT_FAILURE);
			};
		}

		printf("Do you want to continue? 1-yes, 0-no \n");
		scanf("%hhu", &input_continues);
	} while (input_continues);

	four_bytes *subnets = NULL;
	subnets = (four_bytes *)realloc(subnets, sizeof(four_bytes) * count);

	if (! servers)
	{
		fprintf(stderr, "%s", "Failed to allocate memory \n");
		exit(EXIT_FAILURE);
	}
	else
	{
		define_subnets(servers, subnets, count);
		subnet_output(servers, subnets, count);
	}

	if (subnets) free(subnets);
	if (servers) free(servers);
	return EXIT_SUCCESS;
}
