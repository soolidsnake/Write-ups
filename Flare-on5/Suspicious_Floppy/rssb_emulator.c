#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#ifndef DEBUG
#define DEBUG 0
#endif
#define PRINT_IP_OC 0

#define VM_FILE "./rssb_vm.bin"
#define VM_SIZE        23386
#define VM_MAX_ADDRESS  0x25b7
#define VM_ENTRYPOINT 0x015b
#define VM_PASSWORD_OFFSET 0x10E
#define PASSWORD_LENGTH 32

#define NO_PRINT 0
#define PRINT 1

int16_t VM[VM_SIZE] = {0};
int inst_count[0x3000] = {0};
static FILE* log;



void vm(int16_t* vm, int16_t start)
{
	int16_t* ip  = &vm[0];
	int16_t* acc = &vm[1];
    uint64_t count=0;
    uint64_t cnt = 0;
    int16_t res = 0;
    int16_t op = 0;
    int start_log = 0;
    char s[200] = {0};
	vm[2] = 0;

	*ip = start;
	*acc = 0;

	while ( VM_ENTRYPOINT <= *ip && *ip < VM_MAX_ADDRESS && *ip != 2 )
	{
		op = vm[*ip];
        count++;

        start_log = 1;//always log

        count_inst(*ip, NO_PRINT);

        if(start_log)
        {
            snprintf(s, 200, "%.4lx ip = %04hx vm[%04hx] = %04hx - acc = %04hx|  = %04hx\n", count, *ip, op, vm[op], *acc, vm[op] - *acc);
            fwrite(s, sizeof(char), strlen(s), log);
        }

        if (op == -1)
        {
            *ip = *ip + 1;
        }
        else
        {
            res = vm[op] - *acc;

            *acc = res;

            if (op != 2)
            {
                vm[op] = res;
            }


            if (res < 0)
            {
                *ip = *ip + 1;
            }

            *ip = *ip + 1;
        }


        if (vm[6])
        {
            putchar(vm[4]);
            vm[6] = 0;
        }

        if (vm[5])
        {
            vm[3] = getchar();
        }

	}

    printf("%lu\n", cnt);
    printf("#%lu instructions executed.\n", count);
}


void insert_password(int16_t* vm, char* password)
{
    int i=0;
    for(i=0; i<strlen(password); i++)
    {
        vm[VM_PASSWORD_OFFSET + i] = password[i];
    }
}


void count_inst(int16_t ip, int print)
{
    int i = 0;
    #if PRINT_IP_OC == 1
        if(!print)
            inst_count[ip]++;
        else
        {
            for(i = 0; i < sizeof inst_count/4; i++)
            {
                if(inst_count[i] != 0)
                    printf("%x> #%x\n", i, inst_count[i]);
            }
        }
    #endif
}


int main(int argc, char** argv)
{
    int i = 0;

    memset(VM, 0, VM_SIZE);
    int fd = open(VM_FILE, O_RDONLY);
    int n = read(fd, VM, VM_SIZE);
    close(fd);

    log = fopen("log.txt", "w");

    argv[1][32] = 0;
    char* password = strcat(argv[1], "@flare-on.com");//lenght 13

    printf("input> %s\n", password);

    insert_password(VM, password);

    vm(VM, VM_ENTRYPOINT);
    count_inst(0, PRINT);

    fclose(log);
    return 0;
}