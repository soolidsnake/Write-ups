#include <stdio.h>
#include <stdlib.h>
#include "opcodes.h"
#include <sys/mman.h>

typedef unsigned int dword;

#define TRUE (1)

#define REFVMI(base, rva, off) (*(unsigned short*)((dword)(base) + (unsigned short)(rva) + (unsigned short)(off)))

int stop_log = 0;
int in_check = 0;
int iter = 0;
FILE *f;

unsigned short vmip = 0;

int next_inst_skip = 0;



int sub_9D99D(short arg1, short arg2, short arg3)
{
    static const unsigned char* vmentry = ch12_vmi;
    int ret = 0;
    char str[100];
    int i;
    char chr;

    unsigned short val2 = REFVMI(vmentry, arg2 * 2, 0);
    unsigned short val1 = REFVMI(vmentry, arg1 * 2, 0);
    unsigned short tmp  = 0;
    unsigned short val_sub = 0;



    in_check = 1;//comment this to stop priting subleqs

    tmp = val2 - val1;

    REFVMI(vmentry, arg2 * 2, 0) = tmp;
    val_sub = REFVMI(vmentry, arg2 * 2, 0);


    if(0)
    {
        printf("%.4hx> B[%.4hx]{%.4hx} - A[%.4hx]{%.4hx} = ", vmip, arg2, val2, arg1, val1);
        printf("B[%.4hx]{%.4hx} / >%.4hx<", arg2, val_sub, arg3);
        printf("\n");
    }

    if (arg3) 
    {
        if ((signed short)val_sub <= 0 )
        {
            ret = 1;
        }
    }


    return ret;
}

void main(int argc, char **argv)
{


    static const unsigned short vmi_size = 0x2DAD;
    static const unsigned char* vmentry = ch12_vmi;
    vmip = 5;
    short** xvmip = &vmip;
    int chr;
    int i;

    if(argc >= 2)
        in_check =1;

    mprotect(vmentry, vmi_size, PROT_READ|PROT_WRITE);

    for(i=0; i < 32; i++)
       REFVMI(vmentry, 0x1208, i*2) = 0x41;
    printf("\n");

    
    /*********************print flag*********************/
    printf("my input=>    ");
    for(i=0; i < 32; i++)
        printf("%c", REFVMI(vmentry, 0x1208, i*2));
    printf("\n");
    /****************************************************/

    do
    {
        if (vmip + 3 > vmi_size)
            break;

        fflush(stdout);
        if (!sub_9D99D(REFVMI(vmentry, vmip * 2, 0), REFVMI(vmentry, vmip * 2, 2), REFVMI(vmentry, vmip * 2, 4)))
        {
            vmip += 3;
        }
        else
        {
            vmip += 2;
            vmip = REFVMI(vmentry, vmip * 2, 0);
            if (vmip - 0xFFFF == 0)
                break;
        }

        if (REFVMI(vmentry, 8, 0) != 0)
        {
            
            printf("%c", REFVMI(vmentry, 4, 0));
            REFVMI(vmentry, 4, 0) = 0;
            REFVMI(vmentry, 8, 0) = 0;
        }
        iter += 1;

    } while (TRUE);
    
    printf("number of iterations: %d", iter);
}