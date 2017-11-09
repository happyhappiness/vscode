static void check_typos(const char *arg, const struct option *options)
{
	if (strlen(arg) < 3)
		return;

	if (starts_with(arg, "no-")) {
		error ("did you mean `--%s` (with two dashes ?)", arg);
		exit(129);
	}

	for (; options->type != OPTION_END; options++) {
		if (!options->long_name)
			continue;
		if (starts_with(options->long_name, arg)) {
			error ("did you mean `--%s` (with two dashes ?)", arg);
			exit(129);
		}
	}
}