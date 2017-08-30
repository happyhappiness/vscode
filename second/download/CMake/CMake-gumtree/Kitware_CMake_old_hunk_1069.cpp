	if (strcmp(key, "compat-2x")  == 0) {

		/* Handle filnames as libarchive 2.x */

		cpio->init_default_conversion = (val != NULL)?1:0;

		ret = ARCHIVE_OK;

	} else if (strcmp(key, "hdrcharset")  == 0) {

		if (val == NULL || val[0] == 0)

			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

