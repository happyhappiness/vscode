{
	struct shar *shar;

	shar = (struct shar *)a->format_data;
	if (shar == NULL)
		return (ARCHIVE_OK);

	archive_entry_free(shar->entry);
	free(shar->last_dir);
	archive_string_free(&(shar->work));
	archive_string_free(&(shar->quoted_name));
	free(shar);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}