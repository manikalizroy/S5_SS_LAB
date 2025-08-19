#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f1, *f2, *f3, *f4, *f5, *f6;
    char label[30], opcode[30], operand[30], loc[30];
    char symaddr[30], symbol[30];
    char temp_opcode[30], temp_code[30];
    char objcode[30], startaddr[30];
    int length, i;

    f1 = fopen("intermediate.txt", "r");  // from Pass 1
    f2 = fopen("optab.txt", "r");         // opcode table
    f3 = fopen("symtab.txt", "r");        // symbol table
    f4 = fopen("hte.txt", "w");        // HTE object program
    f5 = fopen("length.txt", "r");        // program length
    f6 = fopen("assemlist.txt", "w");       // assembly listing with object code

    if (!f1 || !f2 || !f3 || !f4 || !f5 || !f6)
    {
        printf("Error opening file!!\n");
        return 1;
    }

    fscanf(f5, "Decimal: %d\nHex: %X\n", &length, &length);

    // Print heading for listing file
    //fprintf(f6, "Loc\tLabel\tOpcode\tOperand\tObjectCode\n");

    fscanf(f1, "%s %s %s %s", loc, label, opcode, operand);
    if (strcmp(opcode, "START") == 0)
    {
        strcpy(startaddr, operand);
        fprintf(f4, "H^%s^00%s^%06X\n", label, operand, length);
        fprintf(f6, "%s\t%s\t%s\t%s\t----\n", loc, label, opcode, operand);
        fscanf(f1, "%s %s %s %s", loc, label, opcode, operand);
        fprintf(f4, "T^00%s^", startaddr);  // Start text record
    }

    while (strcmp(opcode, "END") != 0)
    {
        rewind(f2);
        rewind(f3);
        objcode[0] = '\0';

        // Search OPTAB
        while (fscanf(f2, "%s %s", temp_opcode, temp_code) != EOF)
        {
            if (strcmp(opcode, temp_opcode) == 0)
            {
                // search SYMTAB for operand
                while (fscanf(f3, "%s %s", symaddr, symbol) != EOF)
                {
                    if (strcmp(operand, symbol) == 0)
                    {
                        sprintf(objcode, "%s%s", temp_code, symaddr);
                        break;
                    }
                }
                break;
            }
        }

        if (strcmp(opcode, "BYTE") == 0)
        {
            if (operand[0] == 'C') // Character constant
            {
                for (i = 2; i < strlen(operand) - 1; i++)
                {
                    sprintf(objcode + strlen(objcode), "%X", operand[i]);
                }
            }
            else if (operand[0] == 'X') // Hex constant
            {
                strncpy(objcode, operand + 2, strlen(operand) - 3);
                objcode[strlen(operand) - 3] = '\0';
            }
        }
        else if (strcmp(opcode, "WORD") == 0)
        {
            sprintf(objcode, "%06X", atoi(operand));
        }

        // Print into listing file
        if (strlen(objcode) > 0)
        {
            fprintf(f6, "%s\t%s\t%s\t%s\t%s\n", loc, label, opcode, operand, objcode);
            fprintf(f4, "^%s", objcode); // Append to text record
        }
        else
        {
            fprintf(f6, "%s\t%s\t%s\t%s\t----\n", loc, label, opcode, operand);
        }

        fscanf(f1, "%s %s %s %s", loc, label, opcode, operand);
    }

    // End record
    fprintf(f4, "\nE^00%s\n", startaddr);
    fprintf(f6, "%s\t%s\t%s\t%s\t----\n", loc, label, opcode, operand);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    fclose(f6);

    return 0;
}
