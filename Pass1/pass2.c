#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char label[20], opcode[20], operand[30];
    char code[20], mnemonic[20], symbol[20];
    char add[20], objectcode[50];
    int locctr, loc;

    FILE *fp1,*fp2,*fp3,*fp4;

    fp1 = fopen("intermediate.txt","r"); // from Pass1
    fp2 = fopen("twoout.txt","w");       // final Pass2 output
    fp3 = fopen("optab.txt","r");        // OPTAB
    fp4 = fopen("symtab.txt","r");       // SYMTAB

    if(!fp1 || !fp2 || !fp3 || !fp4) {
        printf("Error opening file\n");
        return 1;
    }

    // Read first line (START)
    fscanf(fp1,"%s %s %s",label,opcode,operand);
    if(strcmp(opcode,"START")==0) {
        fprintf(fp2,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(fp1,"%d%s%s%s",&locctr,label,opcode,operand);
    }

    // Process until END
    while(strcmp(opcode,"END")!=0) {
        objectcode[0] = '\0';  // reset
        int found = 0;

        rewind(fp3);  // reset optab file
        while(fscanf(fp3,"%s %s",code,mnemonic) != EOF) {
            if(strcmp(opcode,code)==0) {
                found = 1;
                break;
            }
        }

        if(found) {
            // Look up SYMTAB for operand address
            int symFound = 0;
            rewind(fp4);
            while(fscanf(fp4,"%d %s",&loc,symbol) == 2) {
                if(strcmp(symbol,operand)==0) {
                    symFound = 1;
                    break;
                }
            }
            if(symFound) {
                sprintf(add,"%04X",loc);        // operand address in hex
                strcpy(objectcode,mnemonic);    // opcode hex
                strcat(objectcode,add);         // append operand address
            } else {
                strcpy(objectcode,mnemonic);    // just opcode if no symbol
                strcat(objectcode,"0000");
            }
        }
        else if(strcmp(opcode,"BYTE")==0) {
            if(operand[0]=='C') {
                // convert characters to hex
                objectcode[0] = '\0';
                for(int i=2; i<strlen(operand)-1; i++) {
                    sprintf(add,"%02X",operand[i]);
                    strcat(objectcode,add);
                }
            } else if(operand[0]=='X') {
                // take hex directly
                strncpy(objectcode, operand+2, strlen(operand)-3);
                objectcode[strlen(operand)-3] = '\0';
            }
        }
        else if(strcmp(opcode,"WORD")==0) {
            sprintf(objectcode,"%06X",atoi(operand));  // 3-byte constant
        }
        else if(strcmp(opcode,"RESW")==0 || strcmp(opcode,"RESB")==0) {
            strcpy(objectcode,""); // no object code
        }

        // Print line to output
        fprintf(fp2,"%d\t%s\t%s\t%s\t%s\n",locctr,label,opcode,operand,objectcode);

        // Read next line
        fscanf(fp1,"%d%s%s%s",&locctr,label,opcode,operand);
    }

    // Print END line
    fprintf(fp2,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    return 0;
}
