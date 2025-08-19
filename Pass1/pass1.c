#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f1,*f2,*f3,*f4,*f5;
    char lab[30],opcode[30],operand[30];
    char temp_opcode[30],temp_code[30];
    int locctr=0,x,length,start=0;

    f1=fopen("input.txt","r");
    f2=fopen("optab.txt","r");
    f3=fopen("intermediate.txt","w");
    f4=fopen("symtab.txt","w");
    f5=fopen("length.txt","w");

    if(!f1 || !f2 || !f3 || !f4 ||!f5)
    {
        printf("Error opening file!!\n");
        return 1;
    }

    while(fscanf(f1,"%s %s %s",lab,opcode,operand) !=EOF)
    {
        if (strcmp(opcode, "END") == 0)
        {
            fprintf(f3, "%04X\t%s\t%s\t%s\n",locctr, lab, opcode, operand);
            break;
        }

        x=0;

        if(strcmp(lab, "**") == 0)   //no label is present
        {
            if(strcmp(opcode, "START") == 0)
            {
                start=(int)strtol(operand, NULL, 16);
                locctr=start;
                fprintf(f3, "%04X\t%s\t%s\t%s\n",locctr,lab,opcode,operand);
            }
            else
            {
                rewind(f2);  //Reset the reading position of opcode.txt to the beginning
                while (fscanf(f2, "%s %s",temp_opcode,temp_code) !=EOF)
                {
                    if(strcmp(opcode,temp_opcode)==0)
                    {
                        x=1;
                        break;
                    }
                }
                if(x==1)
                {
                    fprintf(f3, "%04X\t%s\t%s\t%s\n",locctr,lab,opcode,operand);
                    locctr +=3;
                }
            }
        }
        else    //ie labels are present
        {
            fprintf(f4, "%04X\t%s\n", locctr, lab);

            if(strcmp(opcode,"RESW") == 0)
            {
                fprintf(f3, "%04X\t%s\t%s\t%s\n",locctr,lab,opcode,operand);
                locctr +=(3*atoi(operand));
            }
            else if(strcmp(opcode,"WORD") == 0)
            {
                fprintf(f3, "%04X\t%s\t%s\t%s\n",locctr,lab,opcode,operand);
                locctr +=3;
            }
            else if(strcmp(opcode,"BYTE") == 0)
            {
                fprintf(f3, "%04X\t%s\t%s\t%s\n",locctr,lab,opcode,operand);
                if(operand[0] == 'C') // Character constant
                {
                    locctr += strlen(operand) - 3; // exclude C' and '
                }
                else if(operand[0] == 'X') // Hex constant
                {
                    locctr += (strlen(operand) - 3) / 2; // exclude X' and ' , 2 hex digits = 1 byte
                }
            }
            else if(strcmp(opcode,"RESB") == 0)
            {
                fprintf(f3, "%04X\t%s\t%s\t%s\n",locctr,lab,opcode,operand);
                locctr += atoi(operand);
            }
            else
            {
                fprintf(f3, "%04X\t%s\t%s\t%s\n",locctr,lab,opcode,operand);
                locctr += 3;
            }
        }
    }

    length=locctr-start;
    fprintf(f5, "Decimal: %d\nHex: %X\n", length, length);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);

    return 0;
}