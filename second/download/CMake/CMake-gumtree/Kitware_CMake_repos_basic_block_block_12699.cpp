{
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
	}