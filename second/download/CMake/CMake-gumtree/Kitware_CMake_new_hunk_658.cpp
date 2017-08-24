	int ret = ARCHIVE_FAILED;

	if (strcmp(key, "compression") == 0) {
		/*
		 * Set compression to use on all future entries.
		 * This only affects regular files.
		 */
		if (val == NULL || val[0] == 0) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "%s: compression option needs a compression name",
			    a->format_name);
		} else if (strcmp(val, "deflate") == 0) {
#ifdef HAVE_ZLIB_H
			zip->requested_compression = COMPRESSION_DEFLATE;
			ret = ARCHIVE_OK;
#else
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "deflate compression not supported");
#endif
		} else if (strcmp(val, "store") == 0) {
			zip->requested_compression = COMPRESSION_STORE;
			ret = ARCHIVE_OK;
		}
		return (ret);
	} else if (strcmp(key, "experimental") == 0) {
		if (val == NULL || val[0] == 0) {
			zip->flags &= ~ ZIP_FLAG_EXPERIMENT_EL;
		} else {
			zip->flags |= ZIP_FLAG_EXPERIMENT_EL;
		}
		return (ARCHIVE_OK);
	} else if (strcmp(key, "fakecrc32") == 0) {
		/*
		 * FOR TESTING ONLY:  disable CRC calculation to speed up
		 * certain complex tests.
		 */
		if (val == NULL || val[0] == 0) {
			zip->crc32func = real_crc32;
		} else {
			zip->crc32func = fake_crc32;
		}
		return (ARCHIVE_OK);
	} else if (strcmp(key, "hdrcharset")  == 0) {
		/*
		 * Set the character set used in translating filenames.
		 */
		if (val == NULL || val[0] == 0) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "%s: hdrcharset option needs a character-set name",
