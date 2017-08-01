/* Christopher Feener
 * This cannot be used for kernel purposes!!! It is useless.
 * This is a test file for reading XXX /proc/$(pid)/maps.
 * It shall convert virtual addresses to physical addresses.
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Not enough arg's. Please enter PID\n");
		return 1;
	}
	FILE *fin = NULL;
	char filename[100];
	sprintf(filename, "/proc/%s/maps", argv[1]);
	printf("%s\n", filename);
	if ( (fin = fopen(filename, "r")) ==NULL ) {
		printf("Could not open file.\n");
		return 1;
	}
//Start
	char buffer[512];
	int address;
	while ( fgets(buffer, 512, fin) != NULL) {
		sscanf(buffer, "%x", &address);
		printf("%x\n", address);
	}
//End
	return 0;
}
