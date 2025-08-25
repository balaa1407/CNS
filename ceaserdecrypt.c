#include <stdio.h>
#include <ctype.h>
int decryption(char t[500],int k){
 k = k % 26;  // Adjust key for letters

    for (int i = 0; t[i] != '\0'; i++) {
        char ch = t[i];

        if (islower(ch)) {
            ch = ((ch - 'a' - k + 26) % 26) + 'a';
        } else if (isupper(ch)) {
            ch = ((ch - 'A' - k + 26) % 26) + 'A';
        } else if (isdigit(ch)) {
            ch = ((ch - '0' - k + 10) % 10) + '0';
        }
        t[i] = ch;
    }
    }
int main() {
    char text[500];
    int key;

    printf("Enter a message to decrypt: ");
    scanf("%s", text);

    printf("Enter the key: ");
    scanf("%d", &key);

   decryption(text,key);

   

    printf("Decrypted message: %s\n", text);
    return 0;
}

