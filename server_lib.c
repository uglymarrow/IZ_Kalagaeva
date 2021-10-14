/* 
Калагаева Ксения WEB-12
Вариант 26
Создать структуру для хранения информации о сервере: его DNS-имени, IP-адресе, сетевой маске,
количестве процессоров и количестве ядер. Составить с ее использованием программу вывода информации
обо всех серверах с группировкой по подсетям.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

//Функция проверки правильности доменного имени
int validate_domain_name(const char *str)
{
    if (strlen(str) > 255)
    {
        fprintf(stderr, "%s", "Domain name length is too long \n");
        exit(EXIT_FAILURE);
    }

    if (strlen(str) < 2)
    {
        fprintf(stderr, "%s", "Domain name length is too short \n");
        exit(EXIT_FAILURE);
    }

    if (str[0] == '-' || str[strlen(str) - 1] == '-')
    {
        fprintf(stderr, "%s", "Domain name contains '-' symbol at wrong position \n");
        exit(EXIT_FAILURE);
    }

    char spec_sym[] = "`~!@#$%^&*()+=;:',\"{}[]?";
    char *isym;
    isym = strpbrk(str, spec_sym);

    if (!(isym == NULL))
    {
        fprintf(stderr, "%s", "Domain name contains special symbols \n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

//Ввод данных о новом сервере
int input_server_data(server *servers, size_t count)
{
    if (! servers)
    {
        fprintf(stderr, "%s", "Failed to allocate memory \n");
        exit(EXIT_FAILURE);
    }

    //Инициализация структуры
    server cur_server = {"", {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0};

    printf("Input domain name of server: ");
    scanf("%256s", cur_server.domain_name);

    if (validate_domain_name(cur_server.domain_name) != EXIT_SUCCESS)
        exit(EXIT_FAILURE);

    printf("Input IP of server: ");
    scanf("%hhu.%hhu.%hhu.%hhu", &cur_server.ip_address.b1, &cur_server.ip_address.b2,
          &cur_server.ip_address.b3, &cur_server.ip_address.b4);

    printf("Input netmask: ");
    scanf("%hhu.%hhu.%hhu.%hhu", &cur_server.netmask.b1, &cur_server.netmask.b2,
          &cur_server.netmask.b3, &cur_server.netmask.b4);

    printf("Input number of processors: ");
    scanf("%u", &cur_server.proc_num);

    printf("Input number of cores: ");
    scanf("%u", &cur_server.core_num);

    servers[count - 1] = cur_server;

    return EXIT_SUCCESS;
}

//Вывод данных об IP-адресе или маске
void output_four_bytes(four_bytes address)
{
    printf("%hhu.%hhu.%hhu.%hhu\n", address.b1, address.b2,
           address.b3, address.b4);
}

//Вывод данных о сервере
void output_server_data(server cur_server)
{
    printf("Domain name: ");
    printf("%s\n", cur_server.domain_name);
    printf("IP-address: ");
    output_four_bytes(cur_server.ip_address);
    printf("Netmask: ");
    output_four_bytes(cur_server.netmask);
    printf("Number of processors: ");
    printf("%u\n", cur_server.proc_num);
    printf("Number of cores: ");
    printf("%u\n", cur_server.core_num);
}

//Определение массива подсетей для каждого сервера
void define_subnets(server *servers, four_bytes *subnets, size_t count)
{
    if (servers && subnets)
    {
        for (int i = 0; i < count; i++)
        {
            subnets[i].b1 = servers[i].ip_address.b1 & servers[i].netmask.b1;
            subnets[i].b2 = servers[i].ip_address.b2 & servers[i].netmask.b2;
            subnets[i].b3 = servers[i].ip_address.b3 & servers[i].netmask.b3;
            subnets[i].b4 = servers[i].ip_address.b4 & servers[i].netmask.b4;
        }
    }
}

//Сравнение подсетей
int subs_are_equal(four_bytes sub1, four_bytes sub2)
{
    if ((sub1.b1 == sub2.b1) && (sub1.b2 == sub2.b2) && (sub1.b3 == sub2.b3) && (sub1.b4 == sub2.b4))
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}

//Вывод данных о серверах, разделяя по подсетям
void subnet_output(server *servers, four_bytes *subnets, size_t count)
{
    if (!servers || !subnets)
    {
        fprintf(stderr, "%s", "Failed to allocate memory \n");
        exit(EXIT_FAILURE);
    }

    _Bool is_used[count];
    for (int i = 0; i < count; i++)
        is_used[i] = 0;

    for (int i = 0; i < count; i++)
    {
        if (!is_used[i])
        {
            printf("________________________ \n");
            printf("Subnet: ");
            output_four_bytes(subnets[i]);
            is_used[i] = 1;
            output_server_data(servers[i]);
        }

        for (int j = i; j < count; j++)
        {
            if ((!is_used[j]) && (subs_are_equal(subnets[i], subnets[j]) == EXIT_SUCCESS))
            {
                is_used[j] = 1;
                output_server_data(servers[j]);
            }
        }
    }
}
