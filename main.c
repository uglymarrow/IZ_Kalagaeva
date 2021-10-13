
#include <stdio.h>
#include <stdlib.h>

#include "server.h"

int main()
{
	Server *servers = NULL;
	size_t count = 0;
	unsigned char input_continues = 1;

	printf("Input servers data \n");
	do
	{
		count++;
		servers = (Server *)realloc(servers, sizeof(Server) * count);

		if (servers == NULL)
		{
			printf("Failed to allocate memory \n");
			return 0;
		}

		if (!InputServerData(servers, count))
		{
			printf("Failed to input server data \n");
			return 0;
		};

		printf("Do you want to continue? 1-yes, 0-no \n");
		scanf("%hhu", &input_continues);
	} while (input_continues);

	FourBytes subnets[count];
	DefineSubnets(servers, subnets, count);

	SubnetOutput(servers, subnets, count);

	free(servers);
	return 0;
}
