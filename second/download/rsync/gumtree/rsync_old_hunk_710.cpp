 * like `id -G` on Linux, but it's too hard to find a portable
 * equivalent.
 **/

#include "rsync.h"

#ifndef NGROUPS
/* It ought to be defined, but just in case. */
#  define NGROUPS 32
#endif

int
main(UNUSED(int argc), UNUSED(char *argv[]))
{
	int n, i;
	gid_t list[NGROUPS];

	if ((n = getgroups(NGROUPS, list)) == -1) {
		perror("getgroups");
		return 1;
	}

	for (i = 0; i < n; i++) 
		printf("%u ", list[i]);
	printf("\n");
		
	return 0;
}
