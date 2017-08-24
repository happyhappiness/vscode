{
		/* Handle filenames as libarchive 2.x */
		cpio->init_default_conversion = (val != NULL)?1:0;
		return (ARCHIVE_OK);
	}