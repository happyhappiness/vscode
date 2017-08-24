(val == NULL || val[0] == 0) {
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