void argv_array_free_detached(const char **argv)
{
	if (argv) {
		int i;
		for (i = 0; argv[i]; i++)
			free((char **)argv[i]);
		free(argv);
	}
}