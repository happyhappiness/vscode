{
		/* Handle UTF-8 filenames as libarchive 2.x */
		tar->compat_2x = (val != NULL && val[0] != 0);
		tar->init_default_conversion = tar->compat_2x;
		return (ARCHIVE_OK);
	}