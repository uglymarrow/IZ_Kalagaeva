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
int ValidateDomainName(const char *str)
{
    if (strlen(str) > 255)
    {
        printf("Domain name length is too long \n");
        return 0;
    }

    if (strlen(str) < 2)
    {
        printf("Domain name length is too short \n");
        return 0;
    }

    if (str[0] == '-' || str[strlen(str) - 1] == '-')
    {
        printf("Domain name contains '-' symbol at wrong position \n");
        return 0;
    }

    char spec_sym[] = "`~!@#$\%^&*()+=;:',\"{}[]?";
    char *isym;
    isym = strpbrk(str, spec_sym);

    if (!(isym == NULL))
    {
        printf("Domain name contains special symbols \n");
        return 0;
    }

    return 1;
}

//Ввод данных о новом сервере
int InputServerData(Server *servers, size_t count)
{
    //Инициализация структуры
    Server cur_server = {"", {0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0};

    printf("Input domain name of server: ");
    scanf("%256s", cur_server.domain_name);

    if (!ValidateDomainName(cur_server.domain_name))
        return 0;

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

    return 1;
}

//Вывод данных об IP-адресе или маске
void OutputFourBytes(FourBytes address)
{
    printf("%hhu.%hhu.%hhu.%hhu\n", address.b1, address.b2,
           address.b3, address.b4);
}

//Вывод данных о сервере
void OutputServerData(Server cur_server)
{
    printf("Domain name: ");
    printf("%s\n", cur_server.domain_name);
    printf("IP-address: ");
    OutputFourBytes(cur_server.ip_address);
    printf("Netmask: ");
    OutputFourBytes(cur_server.netmask);
    printf("Number of processors: ");
    printf("%u\n", cur_server.proc_num);
    printf("Number of cores: ");
    printf("%u\n", cur_server.core_num);
}

//Определение массива подсетей для каждого сервера
void DefineSubnets(Server *servers, FourBytes subnets[], size_t count)
{
    for (int i = 0; i < count; i++)
    {
        subnets[i].b1 = servers[i].ip_address.b1 & servers[i].netmask.b1;
        subnets[i].b2 = servers[i].ip_address.b2 & servers[i].netmask.b2;
        subnets[i].b3 = servers[i].ip_address.b3 & servers[i].netmask.b3;
        subnets[i].b4 = servers[i].ip_address.b4 & servers[i].netmask.b4;
    }
}

//Сравнение подсетей
_Bool SubsAreEqual(FourBytes sub1, FourBytes sub2)
{
    if ((sub1.b1 == sub2.b1) && (sub1.b2 == sub2.b2) && (sub1.b3 == sub2.b3) && (sub1.b4 == sub2.b4))
        return 1;
    else
        return 0;
}

//Вывод данных о серверах, разделяя по подсетям
void SubnetOutput(Server *servers, FourBytes subnets[], size_t count)
{
    _Bool is_used[count];
    for (int i = 0; i < count; i++)
        is_used[i] = 0;

    for (int i = 0; i < count; i++)
    {
        if (!is_used[i])
        {
            printf("________________________ \n");
            printf("Subnet: ");
            OutputFourBytes(subnets[i]);
            is_used[i] = 1;
            OutputServerData(servers[i]);
        }

        for (int j = i; j < count; j++)
        {
            if ((!is_used[j]) && SubsAreEqual(subnets[i], subnets[j]))
            {
                is_used[j] = 1;
                OutputServerData(servers[j]);
            }
        }
    }
}
