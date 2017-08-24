(val == NULL || val[0] == 0)
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "cpio: hdrcharset option needs a character-set name");
		else {
			cpio->opt_sconv =
			    archive_string_conversion_from_charset(
				&a->archive, val, 0);
			if (cpio->opt_sconv != NULL)
				ret = ARCHIVE_OK;
			else
				ret = ARCHIVE_FATAL;
		}