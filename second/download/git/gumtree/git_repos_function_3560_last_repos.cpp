static int is_rr_file(const char *name, const char *filename, int *variant)
{
	const char *suffix;
	char *ep;

	if (!strcmp(name, filename)) {
		*variant = 0;
		return 1;
	}
	if (!skip_prefix(name, filename, &suffix) || *suffix != '.')
		return 0;

	errno = 0;
	*variant = strtol(suffix + 1, &ep, 10);
	if (errno || *ep)
		return 0;
	return 1;
}