{
	struct ar_w *ar;

	ar = (struct ar_w *)a->format_data;

	if (ar == NULL)
		return (ARCHIVE_OK);

	if (ar->has_strtab > 0) {
		free(ar->strtab);
		ar->strtab = NULL;
	}

	free(ar);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}