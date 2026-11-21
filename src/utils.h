#include <stdlib.h>
#include <stdio.h>

char* getFile (const char *filename) {
	// printf("fn: %s\n", filename);		 // print filename
	FILE* file = fopen(filename, "rb"); // open file
	if (file == NULL) { // check if file opened successfully
		perror("file failed to open");
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	long fileLength = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* fileContents = (char *)malloc(fileLength * sizeof(char) + (1 * sizeof(char)));
	if (fileContents == NULL) {
		perror("mem alloc failed");
		return NULL;
	}

	size_t bytes = fread(fileContents, 1, fileLength, file);
	fileContents[bytes] = '\0';

	printf("FC: %s\n", fileContents);
	fclose(file);
	return fileContents;
}

void* safeRealloc (void* ptr, size_t size, int* errcode) {
	void* newptr = realloc(ptr, size);
	if (newptr == NULL) {
		*errcode = 1;
		newptr = ptr;
	}
	return newptr;
}