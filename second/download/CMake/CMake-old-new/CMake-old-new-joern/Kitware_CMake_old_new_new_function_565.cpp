static int
archive_write_zip_options(struct archive_write *a, const char *key,
    const char *val)
{
	struct zip *zip = a->format_data;
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
	} else if (strcmp(key, "compression-level") == 0) {
		if (val == NULL || !(val[0] >= '0' && val[0] <= '9') || val[1] != '\0') {
			return ARCHIVE_WARN;
		}

		if (val[0] == '0') {
			zip->requested_compression = COMPRESSION_STORE;
			return ARCHIVE_OK;
		} else {
#ifdef HAVE_ZLIB_H
			zip->requested_compression = COMPRESSION_DEFLATE;
			zip->deflate_compression_level = val[0] - '0';
			return ARCHIVE_OK;
#else
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "deflate compression not supported");
#endif
		}
	} else if (strcmp(key, "encryption") == 0) {
		if (val == NULL) {
			zip->encryption_type = ENCRYPTION_NONE;
			ret = ARCHIVE_OK;
		} else if (val[0] == '1' || strcmp(val, "traditional") == 0
		    || strcmp(val, "zipcrypt") == 0
		    || strcmp(val, "ZipCrypt") == 0) {
			if (is_traditional_pkware_encryption_supported()) {
				zip->encryption_type = ENCRYPTION_TRADITIONAL;
				ret = ARCHIVE_OK;
			} else {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "encryption not supported");
			}
		} else if (strcmp(val, "aes128") == 0) {
			if (is_winzip_aes_encryption_supported(
			    ENCRYPTION_WINZIP_AES128)) {
				zip->encryption_type = ENCRYPTION_WINZIP_AES128;
				ret = ARCHIVE_OK;
			} else {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "encryption not supported");
			}
		} else if (strcmp(val, "aes256") == 0) {
			if (is_winzip_aes_encryption_supported(
			    ENCRYPTION_WINZIP_AES256)) {
				zip->encryption_type = ENCRYPTION_WINZIP_AES256;
				ret = ARCHIVE_OK;
			} else {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "encryption not supported");
			}
		} else {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "%s: unknown encryption '%s'",
			    a->format_name, val);
		}
		return (ret);
	} else if (strcmp(key, "experimental") == 0) {
		if (val == NULL || val[0] == 0) {
			zip->flags &= ~ ZIP_FLAG_EXPERIMENT_xl;
		} else {
			zip->flags |= ZIP_FLAG_EXPERIMENT_xl;
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
			    a->format_name);
		} else {
			zip->opt_sconv = archive_string_conversion_to_charset(
			    &a->archive, val, 0);
			if (zip->opt_sconv != NULL)
				ret = ARCHIVE_OK;
			else
				ret = ARCHIVE_FATAL;
		}
		return (ret);
	} else if (strcmp(key, "zip64") == 0) {
		/*
		 * Bias decisions about Zip64: force them to be
		 * generated in certain cases where they are not
		 * forbidden or avoid them in certain cases where they
		 * are not strictly required.
		 */
		if (val != NULL && *val != '\0') {
			zip->flags |= ZIP_FLAG_FORCE_ZIP64;
			zip->flags &= ~ZIP_FLAG_AVOID_ZIP64;
		} else {
			zip->flags &= ~ZIP_FLAG_FORCE_ZIP64;
			zip->flags |= ZIP_FLAG_AVOID_ZIP64;
		}
		return (ARCHIVE_OK);
	}

	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}