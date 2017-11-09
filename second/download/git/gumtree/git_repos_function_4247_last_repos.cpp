const char *archive_format_from_filename(const char *filename)
{
	int i;

	for (i = 0; i < nr_archivers; i++)
		if (match_extension(filename, archivers[i]->name))
			return archivers[i]->name;
	return NULL;
}