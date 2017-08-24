{
		archive_string_init(&str);

		archive_strcat(&str, ARCHIVE_VERSION_STRING);
		if (zlib != NULL) {
			archive_strcat(&str, " zlib/");
			archive_strcat(&str, zlib);
		}
		if (liblzma) {
			archive_strcat(&str, " liblzma/");
			archive_strcat(&str, liblzma);
		}
		if (bzlib) {
			const char *p = bzlib;
			const char *sep = strchr(p, ',');
			if (sep == NULL)
				sep = p + strlen(p);
			archive_strcat(&str, " bz2lib/");
			archive_strncat(&str, p, sep - p);
		}
		if (liblz4) {
			archive_strcat(&str, " liblz4/");
			archive_strcat(&str, liblz4);
		}
	}