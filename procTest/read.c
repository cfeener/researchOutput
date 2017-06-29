/* Christopher Feener
 * This is a test file for reading XXX /proc/$(pid)/maps.
 * It shall convert virtual addresses to physical addresses.
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Not enough arg's.\n");
		return 1;
	}
	FILE *fin = NULL;
	if ( (fin = fopen(argv[1], "r")) ==NULL ) {
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
