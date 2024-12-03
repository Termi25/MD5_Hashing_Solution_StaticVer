#include<stdio.h>
#include<malloc.h>
#include<openssl/md5.h>

int main() {
	unsigned char input[] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
							  0x11,0x02,0x03,0x04,0x55,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
							  0x21,0x02,0x03,0x04,0x65,0x06,0x07,0x08,0x09,0xAA,0x0B,0x0C,0xDD,0x0E,0x0F,
							  0x01,0x02,0x03,0x04,0x75,0x06,0x07,0x08,0x09,0xBA,0x0B,0x0C,0xDD,0x0E };

	printf("Initial input: ");
	for (int i = 0; i < sizeof(input); i++) {
		printf("%02X ", input[i]);
	}
	printf("\n\n");

	MD5_CTX ctx;
	MD5_Init(&ctx);

	unsigned int totalCompleteBlocksOfBytes = (sizeof(input) / MD5_DIGEST_LENGTH) * MD5_DIGEST_LENGTH;

	for (int i = 0; i < totalCompleteBlocksOfBytes; i += MD5_DIGEST_LENGTH) {
		MD5_Update(&ctx, &(input[i]), MD5_DIGEST_LENGTH);
	}

	unsigned int remainingBytes = sizeof(input) % MD5_DIGEST_LENGTH;

	if (remainingBytes > 0) {
		MD5_Update(&ctx, &(input[totalCompleteBlocksOfBytes]), remainingBytes);
	}

	unsigned char result[MD5_DIGEST_LENGTH];
	MD5_Final(result,&ctx);

	printf("MD5 Hash: ");
	for (int i = 0; i < MD5_DIGEST_LENGTH;i++) {
		printf("%02X ", result[i]);
	}
	printf("\n\n");

	return 0;
}