#include "soulfuck.h"
#include "utils.h"

int main (int argc, char** argv) {
	SfEnvironment env;
	setupEnv(&env);
	char* script = getFile(argv[1]);
	if (script[0] == NULL) {
		script = ".";
	}
	execSf(script, &env);
	free(script);
	return 0;
}