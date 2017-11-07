static int sq_dequote_to_argv_internal(char *arg,
				       const char ***argv, int *nr, int *alloc,
				       struct argv_array *array)
{
	char *next = arg;

	if (!*arg)
		return 0;
	do {
		char *dequoted = sq_dequote_step(next, &next);
		if (!dequoted)
			return -1;
		if (argv) {
			ALLOC_GROW(*argv, *nr + 1, *alloc);
			(*argv)[(*nr)++] = dequoted;
		}
		if (array)
			argv_array_push(array, dequoted);
	} while (next);

	return 0;
}