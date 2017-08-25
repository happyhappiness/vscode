static int
archive_read_format_cab_options(struct archive_read *a,
    const char *key, const char *val)
{
	struct cab *cab;
	int ret = ARCHIVE_FAILED;

	cab = (struct cab *)(a->format->data);
	if (strcmp(key, "hdrcharset")  == 0) {
		if (val == NULL || val[0] == 0)
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "cab: hdrcharset option needs a character-set name");
		else {
			cab->sconv = archive_string_conversion_from_charset(
			    &a->archive, val, 0);
			if (cab->sconv != NULL)
				ret = ARCHIVE_OK;
			else
				ret = ARCHIVE_FATAL;
		}
	} else
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "cab: unknown keyword ``%s''", key);

	return (ret);
}