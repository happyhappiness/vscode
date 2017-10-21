

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "usage: " PROGRAM " DIR ...\n"
			"Trivial file listing program for portably checking rsync\n");
		return 1;
	}

	for (argv++; *argv; argv++) {
		list_file(*argv);
	}

	return 0;
}
