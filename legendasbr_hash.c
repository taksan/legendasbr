#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int64_t charTo64bitNum(unsigned char a[]) {
	int64_t n=0;
	memcpy(&n, a, 8);  
	return n;
}

void int64ToChar(unsigned char a[], int64_t n)
{
	memcpy(a, &n, 8);
}

void print_buffer(unsigned char * buffer) {
	int i;
	for (i=0; i < 8; i++) {
		printf("%d ", buffer[i]);
	}
	printf("\n");
}

int main(int argc, char ** argv)
{
	if (argc < 2) {
		printf("Missing file name\n");
		return -1;
	}
	FILE * fp = fopen(argv[1], "r");
	fseek(fp, 0, SEEK_END);
	int64_t length=ftell(fp);
	int64_t num2 = length;
	int64_t num3 = 0;

	fseek(fp, 0, SEEK_SET);

	unsigned char buffer[8];
	while( (num3 < 0x2000) && fread(buffer, sizeof(char), 8, fp)>0) {
		num3++;
		num2 +=	charTo64bitNum(buffer);
	}
	
	fseek(fp, length-0x10000, SEEK_SET);
	num3 = 0;

	while( (num3<0x2000) && fread(buffer, sizeof(char), 8, fp)>0 ) {
		num3++;
		num2 += charTo64bitNum(buffer);	
	}

	fclose(fp);

	int64ToChar(buffer,num2);

	unsigned char reverse [8];
	int i;
	for (i=7; i >=0; i--) 
		reverse[7-i] = buffer[i];

	for (i=0; i <8; i++)
		printf("%02x", reverse[i]);


	printf("\n");
	return 0;
}
