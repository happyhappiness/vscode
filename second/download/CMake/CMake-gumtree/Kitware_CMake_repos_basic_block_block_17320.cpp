{
		const char *name = NULL;

		if (value == NULL)
			xar->opt_compression = NONE;
		else if (strcmp(value, "gzip") == 0)
			xar->opt_compression = GZIP;
		else if (strcmp(value, "bzip2") == 0)
#if defined(HAVE_BZLIB_H) && defined(BZ_CONFIG_ERROR)
			xar->opt_compression = BZIP2;
#else
			name = "bzip2";
#endif
		else if (strcmp(value, "lzma") == 0)
#if HAVE_LZMA_H
			xar->opt_compression = LZMA;
#else
			name = "lzma";
#endif
		else if (strcmp(value, "xz") == 0)
#if HAVE_LZMA_H
			xar->opt_compression = XZ;
#else
			name = "xz";
#endif
		else {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "Unknown compression name: `%s'",
			    value);
			return (ARCHIVE_FAILED);
		}
		if (name != NULL) {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "`%s' compression not supported "
			    "on this platform",
			    name);
			return (ARCHIVE_FAILED);
		}
		return (ARCHIVE_OK);
	}