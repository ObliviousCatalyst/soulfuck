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
	(*env).array = (int*)calloc(256, sizeof(int));
}

void execSf (char* sfCode, SfEnvironment* env) {
	int length = strlen(sfCode);
	int loopback = -1;
	for (int pt = 0; pt < length; pt++) {
		char current = sfCode[pt];
		switch (current) {
			case '>':
				env->pointer++;
				if (env->pointer > env->arrLength - 1) {
					env->pointer = 0;
				}
			break;

			case '<':
				env->pointer--;
				if (env->pointer < 0) {
					env->pointer = env->arrLength - 1;
				}
			break;

			case '+':
				env->array[env->pointer]++;
			break;
			
			case '-':
				env->array[env->pointer]--;
			break;

			case '.':
				printf("%c", (char)env->array[env->pointer]);
			break;

			case ',':
				scanf("%d", &env->array[env->pointer]);
			break;

			case '[':
				loopback = pt;
			break;

			case ']':
				if (loopback == -1) {
					break;
				}
				if (env->array[env->pointer] != 0) {
					pt = loopback;
				}
			break;

			case '#':
				pt++;
				while (sfCode[pt] != '#') {
					pt++;
				}
			break;

			case 'c':
			case 'C':
				env->stored = env->array[env->pointer];
			break;

			case 'p':
			case 'P':
				env->array[env->pointer] = env->stored;
			break;
		}
	}
}