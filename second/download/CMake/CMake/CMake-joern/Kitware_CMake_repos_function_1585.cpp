static int
archive_read_format_tar_options(struct archive_read *a,
    const char *key, const char *val)
{
	struct tar *tar;
	int ret = ARCHIVE_FAILED;

	tar = (struct tar *)(a->format->data);
	if (strcmp(key, "compat-2x")  == 0) {
		/* Handle UTF-8 filenames as libarchive 2.x */
		tar->compat_2x = (val != NULL && val[0] != 0);
		tar->init_default_conversion = tar->compat_2x;
		return (ARCHIVE_OK);
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
		return (ret);
	} else if (strcmp(key, "mac-ext") == 0) {
		tar->process_mac_extensions = (val != NULL && val[0] != 0);
		return (ARCHIVE_OK);
	} else if (strcmp(key, "read_concatenated_archives") == 0) {
		tar->read_concatenated_archives = (val != NULL && val[0] != 0);
		return (ARCHIVE_OK);
	}

	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}