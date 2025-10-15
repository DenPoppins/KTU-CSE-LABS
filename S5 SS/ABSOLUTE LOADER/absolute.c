#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int main(void){
    char line[512], progname[64], user[64];
    FILE *fp = fopen("objcode.txt", "r");
	fscanf(fp, "%511s", line);
 
    char *tok = strtok(line, "^");      // "H"
    tok = strtok(NULL, "^");            // program name

    strncpy(progname, tok, sizeof(progname)-1);
    progname[sizeof(progname)-1] = '\0';

    printf("Enter the program name: ");
    scanf("%63s", user);

    if(strcmp(user, progname) != 0){
        printf("Invalid program name!\n");
        fclose(fp);
        return 1;
    }

    while(fscanf(fp, "%511s", line) == 1){
        if(line[0] == 'T'){
            tok = strtok(line, "^");            // "T"
            char *start_s = strtok(NULL, "^");  // start address
            strtok(NULL, "^");                   // length (ignored)

            unsigned int addr = strtoul(start_s, NULL, 16);

            char *objtok;
            while((objtok = strtok(NULL, "^"))){
                for(size_t i = 0; i + 1 < strlen(objtok); i += 2){
                    printf("%04X\t%C%C\n", addr, objtok[i], objtok[i+1]);
                    addr++;
                }
            }
        } else if(line[0] == 'E'){
            break;
        }
    }

    fclose(fp);
    return 0;
}
