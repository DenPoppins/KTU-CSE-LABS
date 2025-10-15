#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main() {
    // Open the necessary files
    FILE *inter = fopen("intermediate.txt", "r"); // intermediate file generated after Pass 1
    FILE *symtab = fopen("symtab.txt", "r");     // symbol table
    FILE *optab = fopen("optab.txt", "r");       // operation code table
    FILE *obj = fopen("objcode.txt", "w");       // output object code file
    FILE *lengthf = fopen("length.txt", "r");    // program length file

    // Variables to store contents of files
    char locctr[10], label[10], opcode[10], operand[10]; // fields from intermediate file
    char mnemonic[10], code[10], symbol[10], saddr[10]; // used for OPTAB and SYMTAB
    char prglen[10], trec[100];                         // program length and text record
    int straddr, tlen = 0;                              // starting address and text record length

    // Read program length from length.txt
    fscanf(lengthf, "%s", prglen);

    // Read first line from intermediate file (typically START directive)
    fscanf(inter, "%s%s%s%s", locctr, label, opcode, operand);

    // Write header record to object code file
    fprintf(obj, "H^%s^00%s^%s\n", label, locctr, prglen);

    // Store starting address for end record
    straddr = atoi(locctr);

    // Read next line from intermediate file (first instruction)
    fscanf(inter, "%s%s%s%s", locctr, label, opcode, operand);

    // Initialize text record with starting address (T record)
    sprintf(trec, "T^00%s^##", locctr);

    // Process instructions until END directive is encountered
    while(strcmp(opcode, "END") != 0) {
        int found = 0;

        // Check if opcode exists in the operation table
        rewind(optab); // reset file pointer to beginning
        while(fscanf(optab, "%s%s", mnemonic, code) != EOF) {
            if(strcmp(opcode, mnemonic) == 0) {
                // If found, append opcode's machine code to text record
                sprintf(trec + strlen(trec), "^%s", code);
                tlen += 3;  // assuming instruction length is 3 bytes
                found = 1;
                break;
            }
        }

        // Look up the symbol in the symbol table to get its address
        rewind(symtab); // reset file pointer to beginning
        while(fscanf(symtab, "%s%s", symbol, saddr) != EOF) {
            if(strcmp(operand, symbol) == 0) {
                sprintf(trec + strlen(trec), "%s", saddr);
                break;
            }
        }

        // Handle WORD directive (store 3-byte constant in object code)
        if(strcmp(opcode, "WORD") == 0) {
            sprintf(trec + strlen(trec), "^%06X", atoi(operand)); // convert operand to 6-digit hex
            tlen += 3;
        } 
        // Handle BYTE directive (store character or hex constants)
        else if(strcmp(opcode, "BYTE") == 0) {
            int i = 2; // skip C' or X'
            sprintf(trec + strlen(trec), "^");
            while(operand[i+1] != '\0') {
                sprintf(trec + strlen(trec), "%X", operand[i]); // convert each character to hex
                i++;
                tlen++;
            }
        }

        // Read next instruction from intermediate file
        fscanf(inter, "%s%s%s%s", locctr, label, opcode, operand);
    }

    // Update text record length in the record (T record)
    tlen++; // adjust length
    trec[10] = (tlen % 10) + '0';
    tlen /= 10;
    trec[9] = (tlen % 10) + '0';

    // Write text record to object code file
    fprintf(obj, "%s\n", trec);

    // Write end record to object code file with starting address
    fprintf(obj, "E^%06d\n", straddr);

    // Close all files
    fclose(inter);
    fclose(symtab);
    fclose(optab);
    fclose(obj);
    fclose(lengthf);
}
