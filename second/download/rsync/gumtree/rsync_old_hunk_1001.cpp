 * Always returns 0 unless something extraordinary happens. */

#include "rsync.h"

int dry_run = 0;
int am_root = 0;
int read_only = 0;
int list_only = 0;
int verbose = 0;
int preserve_perms = 0;
int preserve_executability = 0;

int
main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "usage: t_unsafe LINKDEST SRCDIR\n");
