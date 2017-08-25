static int
archive_read_format_lha_options(struct archive_read *a,
    const char *key, const char *val)
{
	struct lha *lha;
	int ret = ARCHIVE_FAILED;

	lha = (struct lha *)(a->format->data);
	if (strcmp(key, "hdrcharset")  == 0) {
		if (val == NULL || val[0] == 0)
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "lha: hdrcharset option needs a character-set name");
		else {
			lha->opt_sconv =
			    archive_string_conversion_from_charset(
				&a->archive, val, 0);
			if (lha->opt_sconv != NULL)
				ret = ARCHIVE_OK;
			else
				ret = ARCHIVE_FATAL;
		}
	} else
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "lha: unknown keyword ``%s''", key);

	return (ret);
}