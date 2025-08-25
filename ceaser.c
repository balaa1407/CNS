#include <stdio.h>
#include <ctype.h>

void encryption(char t[], int k) {
    k = k % 26;

    for (int i = 0; t[i] != '\0'; i++) {
        char ch = t[i];

        if (islower(ch)) {
            ch = ((ch - 'a' + k) % 26) + 'a';
        } else if (isupper(ch)) {
            ch = ((ch - 'A' + k) % 26) + 'A';
        } else if (isdigit(ch)) {
            ch = ((ch - '0' + k) % 10) + '0';
        } else {
            // For other characters, just skip encryption, keep as is.
            // Or optionally print invalid character once
            printf("Invalid Character: %c\n", ch);
            // Leave ch unchanged
        }
        t[i] = ch;
    }
}

int main() {
    char text[500];
    int key;

    printf("Enter a message to encrypt: ");
    // Use fgets to read spaces as well
    fgets(text, sizeof(text), stdin);

    // Remove trailing newline if present
    int len = 0;
    while (text[len] != '\0') len++;
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    printf("Enter the key: ");
    scanf("%d", &key);

    encryption(text, key);
    printf("Encrypted message: %s\n", text);

    return 0;
}

