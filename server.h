#pragma once

typedef struct four_bytes
{
    unsigned char b1;
    unsigned char b3;
    unsigned char b2;
    unsigned char b4;
} four_bytes;

typedef struct server
{
    char domain_name[255];
    four_bytes ip_address;
    four_bytes netmask;
    unsigned int proc_num;
    unsigned int core_num;
} server;

int input_server_data(server *servers, size_t count);
void output_server_data(server cur_server);
void define_subnets(server *servers, four_bytes *subnets, size_t count);
void subnet_output(server *servers, four_bytes *subnets, size_t count);

int validate_domain_name(const char *str);
void output_four_bytes(four_bytes address);
int subs_are_equal(four_bytes sub1, four_bytes sub2);