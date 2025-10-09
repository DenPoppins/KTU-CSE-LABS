#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
int hexlen(int n) { 
    int len = 0; 
    while(n) { n /= 16; len++; } 
    return (len == 0 ? 1 : len); 
}

void main() { 
    FILE *inter = fopen("intermediate.txt", "r"); 
    FILE *symtab = fopen("symtab.txt", "r"); 
    FILE *optab = fopen("optab.txt", "r"); 
    FILE *obj = fopen("objcode.txt", "w"); 
    FILE *lengthf = fopen("length.txt", "r"); 
    char locctr[10], label[10], opcode[10], operand[10]; 
    char mnemonic[10], code[10], symbol[10], saddr[10]; 
    char prglen[10], trec[100]; 
    int straddr, tlen = 0; 
    fscanf(lengthf, "%s", prglen); 
    fscanf(inter, "%s%s%s%s", locctr, label, opcode, operand); 
    fprintf(obj, "H^%s^00%s^%s\n", label, locctr, prglen); 
    straddr = atoi(locctr); 
    fscanf(inter, "%s%s%s%s", locctr, label, opcode, operand); 
    sprintf(trec, "T^00%s^##", locctr); 
    
    while(strcmp(opcode, "END") != 0) { 
        int found = 0; 
        rewind(optab); 
        while(fscanf(optab, "%s%s", mnemonic, code) != EOF) { 
            if(strcmp(opcode, mnemonic) == 0) { 
                sprintf(trec + strlen(trec), "^%s", code); 
                tlen += 3;  
                found = 1; 
                break; 
            } 
        } 
        rewind(symtab); 
        while(fscanf(symtab, "%s%s", symbol, saddr) != EOF) { 
            if(strcmp(operand, symbol) == 0) { 
                sprintf(trec + strlen(trec), "%s", saddr); 
                break; 
            } 
        } 
 
        if(strcmp(opcode, "WORD") == 0) { 
            sprintf(trec + strlen(trec), "^%06X", atoi(operand)); 
            tlen += 3; 
        } else if(strcmp(opcode, "BYTE") == 0) { 
            int i = 2; 
            sprintf(trec + strlen(trec), "^"); 
            while(operand[i+1] != '\0') { 
                sprintf(trec + strlen(trec), "%X", operand[i]); 
                i++; 
                tlen++; 
            } 
        } 
        fscanf(inter, "%s%s%s%s", locctr, label, opcode, operand); 
    } 
    tlen++; 
    trec[10] = (tlen % 10) + '0'; 
    tlen /= 10; 
    trec[9] = (tlen % 10) + '0'; 
    fprintf(obj, "%s\n", trec); 
    fprintf(obj, "E^%06X\n", straddr); 
    fclose(inter); 
    fclose(symtab); 
    fclose(optab); 
    fclose(obj); 
    fclose(lengthf); 
}