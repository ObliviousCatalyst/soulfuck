#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct SfEnvironment SfEnvironment;

struct SfEnvironment {
	unsigned int pointer;
	unsigned int arrLength;
	int* array;
	long stored;
};

int setupEnv (SfEnvironment* env) {
	(*env).pointer = 0;
	(*env).arrLength = 256;
	(*env).pointer = (int*)calloc(256, sizeof(int));
}

void execSf (char* sfCode, SfEnvironment* env) {
	int length = strlen(sfCode);
	int loopback = -1;
	for (int pt = 0; pt < length; pt++) {
		char current = sfCode[pt];
		switch (current) {
			case '>':
				env->pointer++;
			break;

			case '<':
				env->pointer--;
			break;

			case '+':
				env->array[env->pointer]++;
			break;
			
			case '-':
				env->array[env->pointer]--;
			break;

			case '.':
				printf("%d", env->array[env->pointer]);
			break;

			case ',':
				printf("\ninput: ");
				scanf("%d", &env->array[env->pointer]);
				printf("\n");
			break;

			case '[':
				loopback = pt;
			break;

			case ']':
				if (loopback == -1) {
					break;
				}
				if (env->array[env->pointer] != 0) {
					pt = loopback;;
				}
			break;
		}
	}
}