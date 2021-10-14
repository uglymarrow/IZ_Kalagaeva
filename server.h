#pragma once

typedef struct FourBytes
{
    unsigned char b1;
    unsigned char b3;
    unsigned char b2;
    unsigned char b4;
} FourBytes;

typedef struct Server
{
    char domain_name[255];
    FourBytes ip_address;
    FourBytes netmask;
    unsigned int proc_num;
    unsigned int core_num;
} Server;

int InputServerData(Server *servers, size_t count);
void OutputServerData(Server cur_server);
void DefineSubnets(Server *servers, FourBytes subnets[], size_t count);
void SubnetOutput(Server *servers, FourBytes subnets[], size_t count);

int ValidateDomainName(const char *str);
void OutputFourBytes(FourBytes address);