int cmd_var(int argc, const char **argv, const char *prefix)
{
	const char *val = NULL;
	if (argc != 2)
		usage(var_usage);

	if (strcmp(argv[1], "-l") == 0) {
		git_config(show_config, NULL);
		list_vars();
		return 0;
	}
	git_config(git_default_config, NULL);
	val = read_var(argv[1]);
	if (!val)
		usage(var_usage);

	printf("%s\n", val);

	return 0;
}