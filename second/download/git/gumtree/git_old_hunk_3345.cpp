static int truncate_fetch_head(void)
{
	const char *filename = git_path_fetch_head();
	FILE *fp = fopen_for_writing(filename);

	if (!fp)
		return error(_("cannot open %s: %s\n"), filename, strerror(errno));
	fclose(fp);
	return 0;
}

static void set_option(struct transport *transport, const char *name, const char *value)
{
