#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <unistd.h>
#include <stdlib.h>

int next_password(char *password) {
	int index = strlen(password) - 1;

	while (password[index] == 'z') {
		password[index] = 'a';
		index--;
		if (index == -1) {
			return 0;
		}
	}

	password[index]++;
	return 1;
}

int main (void) {
	char hash_to_crack[SHA256_DIGEST_LENGTH * 2 + 1];

	printf("Enter the hash to crack: ");
	fgets(hash_to_crack, SHA256_DIGEST_LENGTH * 2 + 1, stdin);

	int password_len;
	printf("Enter password length: ");
	scanf("%d", &password_len);

	char password[password_len + 1];
	memset(password, 'a', password_len);
	password[password_len] = 0;

	unsigned char current_hash[SHA256_DIGEST_LENGTH];
	char current_hash_string[SHA256_DIGEST_LENGTH * 2 + 1];
	int i;

	do {
		SHA256(password, password_len, current_hash);
		current_hash_string[0] = 0;

		for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
			sprintf(current_hash_string, "%s%02x", current_hash_string, current_hash[i]);

		if (strncmp(current_hash_string, hash_to_crack, SHA256_DIGEST_LENGTH * 2) == 0) {
			printf("FOUND PASSWORD\nPass: %s\n", password);
			break;
		}

	} while(next_password(password) == 1);

	return 0;
}
