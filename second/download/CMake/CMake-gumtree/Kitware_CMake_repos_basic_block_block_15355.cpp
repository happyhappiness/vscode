(strcmp(key, "compression-level") == 0) {
		if (value == NULL ||
		    !(value[0] >= '0' && value[0] <= '9') ||
		    value[1] != '\0') {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "Illegal value `%s'",
			    value);
			return (ARCHIVE_FAILED);
		}
		zip->opt_compression_level = value[0] - '0';
		return (ARCHIVE_OK);
	}