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

    /********init_next_inst*********/
    short next_arg2 = 0;
    short next_arg1 = 0;
    unsigned short next_val2 = 0;
    unsigned short next_val1 = 0;

    short next1_arg2 = 0;
    short next1_arg1 = 0;
    unsigned short next1_val2 = 0;
    unsigned short next1_val1 = 0;

    short next2_arg2 = 0;
    short next2_arg1 = 0;
    unsigned short next2_val2 = 0;
    unsigned short next2_val1 = 0;
    /******************************/



    in_check = 1;//comment this to stop priting subleqs

    tmp = val2 - val1;
    REFVMI(vmentry, arg2 * 2, 0) = tmp;


    val_sub = REFVMI(vmentry, arg2 * 2, 0);


    if(next_inst_skip)
    {
        next_inst_skip--;
        return ret;
    }

    if(!arg3 || (signed short)val_sub > 0)
    {

            //CHECK IF ADD: //checked works perfectly
            if(val2 == 0 && val1 != 0)//subleq a, Z
            {
                next_arg2 = REFVMI(vmentry, (vmip+3) * 2, 2);
                next_arg1 = REFVMI(vmentry, (vmip+3) * 2, 0);

                next_val2 = REFVMI(vmentry, next_arg2 * 2, 0);
                next_val1 = REFVMI(vmentry, next_arg1 * 2, 0);   
                

                if(next_val2 != 0 && (signed short)next_val1 == -val1)//subleq Z, b
                {
                    next1_arg2 = REFVMI(vmentry, (vmip+6) * 2, 2);
                    next1_arg1 = REFVMI(vmentry, (vmip+6) * 2, 0);

                    next1_val2 = REFVMI(vmentry, next1_arg2 * 2, 0);
                    next1_val1 = REFVMI(vmentry, next1_arg1 * 2, 0); 

                    if(next1_arg2*2 == next1_arg1*2)//subleq Z, Z//THEN ITS AN ADD
                    {
                        if(in_check)
                            {
                                printf("%.4hx> add [%.4hx]{%.4hx}, [%.4hx]{%.4hx}; #%.4hx", vmip, next_arg2, next_val2, arg1, val1, next_val2 + val1);
                                printf("\n");
                            }

                        next_inst_skip = 2;
                        return 0;
                    }                      
                }
            }


            //CHECK IF MOV: 
            if(arg2*2 == arg1*2)//subleq b, b/correct
            {
                if(vmip == 0x09)
                    printf("");
                next_arg2 = REFVMI(vmentry, (vmip+3) * 2, 2);
                next_arg1 = REFVMI(vmentry, (vmip+3) * 2, 0);

                next_val2 = REFVMI(vmentry, next_arg2 * 2, 0);
                next_val1 = REFVMI(vmentry, next_arg1 * 2, 0);                   

                if(next_val2 == 0 && next_val1 != 0)//subleq a, Z
                {
                    next1_arg2 = REFVMI(vmentry, (vmip+6) * 2, 2);
                    next1_arg1 = REFVMI(vmentry, (vmip+6) * 2, 0);

                    next1_val2 = REFVMI(vmentry, next1_arg2 * 2, 0);
                    next1_val1 = REFVMI(vmentry, next1_arg1 * 2, 0);   

                    if(next1_val2 == 0 && next1_arg2*2 == arg2*2 && next1_arg1*2 == 0)//subleq Z, b
                    {
                        next2_arg2 = REFVMI(vmentry, (vmip+9) * 2, 2);
                        next2_arg1 = REFVMI(vmentry, (vmip+9) * 2, 0);

                        next2_val2 = REFVMI(vmentry, next2_arg2 * 2, 0);
                        next2_val1 = REFVMI(vmentry, next2_arg1 * 2, 0);   

                        if(next2_arg2*2 == next2_arg1*2)//subleq Z, Z// THEN ITS A MOV
                        {
                            if(in_check)
                            {
                                printf("%.4hx> mov [%.4hx], [%.4hx]{%.4hx}", vmip, arg2, next_arg1, next_val1);
                                printf("\n");
                            }
                            //vmip = vmip + 3*3;

                            next_inst_skip = 3;
                            
                            return 0;
                        } 
                    }
                }
            }

    }


    if (arg3) 
    {
        if ((signed short)val_sub <= 0 )
        {
            if(val2 == 0 && val1 == 0)
            {
                if(in_check)
                {
                    printf("%.4hx> jmp %.4hx", vmip, arg3);
                    printf("\n");
                }
                return 1;
            }

            ret = 1;
        }
    }

    if(val2 == 0 && val1 == 0 && arg3 == 0)
        return ret;

    if(val2 != 0 && val1 == 0 && arg3 == 0)
        return ret;


    if(in_check)
    {
        printf("%.4hx> B[%.4hx]{%.4hx} - A[%.4hx]{%.4hx} = ", vmip, arg2, val2, arg1, val1);
        printf("B[%.4hx]{%.4hx} / >%.4hx<", arg2, val_sub, arg3);
        
        printf("\n");
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

    /*********************print flag*********************/
    printf("my input=>    ");
    for(i=0; i < 32; i++)
        printf("%c", REFVMI(vmentry, 0x1208, i*2));
    printf("\n");
    /****************************************************/


    f = fopen("log_eip", "w");

    do
    {
        if (vmip + 3 > vmi_size)
            break;

        fflush(stdout);

        char st[30];
        int l = vmip*2;
        sprintf(st, "%d", l);
        fprintf(f, "%s\n", st);

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
    
}