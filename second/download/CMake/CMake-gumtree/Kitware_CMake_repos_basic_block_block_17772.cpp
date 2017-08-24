{
	struct archive_write *a = (struct archive_write *)_a;

	if (a->format_name == NULL)
		return (m == NULL)?ARCHIVE_FAILED:ARCHIVE_WARN - 1;
	/* If the format name didn't match, return a special code for
	 * _archive_set_option[s]. */
	if (m != NULL && strcmp(m, a->format_name) != 0)
		return (ARCHIVE_WARN - 1);
	if (a->format_options == NULL)
		return (ARCHIVE_WARN);
	return a->format_options(a, o, v);
}