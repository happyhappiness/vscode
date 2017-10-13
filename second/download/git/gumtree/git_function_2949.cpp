static int read_mailmap_file(struct string_list *map, const char *filename,
			     char **repo_abbrev)
{
	char buffer[1024];
	FILE *f;

	if (!filename)
		return 0;

	f = fopen(filename, "r");
	if (!f) {
		if (errno == ENOENT)
			return 0;
		return error("unable to open mailmap at %s: %s",
			     filename, strerror(errno));
	}

	while (fgets(buffer, sizeof(buffer), f) != NULL)
		read_mailmap_line(map, buffer, repo_abbrev);
	fclose(f);
	return 0;
}