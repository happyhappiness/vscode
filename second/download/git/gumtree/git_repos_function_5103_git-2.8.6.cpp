static int output_directory_callback(const struct option *opt, const char *arg,
			      int unset)
{
	const char **dir = (const char **)opt->value;
	if (*dir)
		die(_("Two output directories?"));
	*dir = arg;
	return 0;
}