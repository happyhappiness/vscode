int
main(int argc, char **argv)
{
	int i;

	if (argc <= 1) {
		fprintf(stderr, "trimslash: needs at least one argument\n");
		return 1;
	}

	for (i = 1; i < argc; i++) {
		trim_trailing_slashes(argv[i]);	/* modify in place */
		printf("%s\n", argv[i]);
	}
	return 0;
}