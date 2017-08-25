static int
archive_read_format_tar_options(struct archive_read *a,
    const char *key, const char *val)
{
	struct tar *tar;
	int ret = ARCHIVE_FAILED;

	tar = (struct tar *)(a->format->data);
	if (strcmp(key, "compat-2x")  == 0) {
		/* Handle UTF-8 filnames as libarchive 2.x */
		tar->compat_2x = (val != NULL)?1:0;
		tar->init_default_conversion = tar->compat_2x;
		ret = ARCHIVE_OK;
	} else if (strcmp(key, "hdrcharset")  == 0) {
		if (val == NULL || val[0] == 0)
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "tar: hdrcharset option needs a character-set name");
		else {
			tar->opt_sconv =
			    archive_string_conversion_from_charset(
				&a->archive, val, 0);
			if (tar->opt_sconv != NULL)
				ret = ARCHIVE_OK;
			else
				ret = ARCHIVE_FATAL;
		}
	} else
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "tar: unknown keyword ``%s''", key);

	return (ret);
}