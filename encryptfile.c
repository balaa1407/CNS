#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void encrypt_line(char line[], int k) {
    k = k % 26;
    for (int i = 0; line[i] != '\0'; i++) {
        char ch = line[i];
        if (islower(ch)) {
            ch = ((ch - 'a' + k) % 26) + 'a';
        } else if (isupper(ch)) {
            ch = ((ch - 'A' + k) % 26) + 'A';
        } else if (isdigit(ch)) {
            ch = ((ch - '0' + k) % 10) + '0';
        }
        // leave other characters unchanged (spaces, punctuation)
        line[i] = ch;
    }
}

void decrypt_line(char line[], int k) {
    k = k % 26;
    for (int i = 0; line[i] != '\0'; i++) {
        char ch = line[i];
        if (islower(ch)) {
            ch = ((ch - 'a' - k + 26) % 26) + 'a';
        } else if (isupper(ch)) {
            ch = ((ch - 'A' - k + 26) % 26) + 'A';
        } else if (isdigit(ch)) {
            ch = ((ch - '0' - k + 10) % 10) + '0';
        }
        // leave other characters unchanged
        line[i] = ch;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <inputfile> <outputfile> <key> <mode>\n", argv[0]);
        printf("mode: encrypt or decrypt\n");
        return 1;
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];
    int key = atoi(argv[3]);
    char *mode = argv[4];

    FILE *fin = fopen(input_filename, "r");
    if (!fin) {
        perror("Error opening input file");
        return 1;
    }

    FILE *fout = fopen(output_filename, "w");
    if (!fout) {
        perror("Error opening output file");
        fclose(fin);
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fin)) {
        if (strcmp(mode, "encrypt") == 0) {
            encrypt_line(line, key);
        } else if (strcmp(mode, "decrypt") == 0) {
            decrypt_line(line, key);
        } else {
            printf("Invalid mode. Use 'encrypt' or 'decrypt'.\n");
            fclose(fin);
            fclose(fout);
            return 1;
        }
        fputs(line, fout);
    }

    fclose(fin);
    fclose(fout);

    printf("Operation '%s' completed. Output written to '%s'\n", mode, output_filename);
    return 0;
}
