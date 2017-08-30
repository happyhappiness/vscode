		/* Handle UTF-8 filnames as libarchive 2.x */
		tar->compat_2x = (val != NULL)?1:0;
		tar->init_default_conversion = tar->compat_2x;
		return (ARCHIVE_OK);
	} else if (strcmp(key, "hdrcharset")  == 0) {
		if (val == NULL || val[0] == 0)
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
