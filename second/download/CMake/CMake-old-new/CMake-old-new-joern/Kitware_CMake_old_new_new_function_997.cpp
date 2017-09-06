static int
xar_options(struct archive_write *a, const char *key, const char *value)
{
	struct xar *xar;

	xar = (struct xar *)a->format_data;

	if (strcmp(key, "checksum") == 0) {
		if (value == NULL)
			xar->opt_sumalg = CKSUM_NONE;
		else if (strcmp(value, "sha1") == 0)
			xar->opt_sumalg = CKSUM_SHA1;
		else if (strcmp(value, "md5") == 0)
			xar->opt_sumalg = CKSUM_MD5;
		else {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "Unknown checksum name: `%s'",
			    value);
			return (ARCHIVE_FAILED);
		}
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "compression") == 0) {
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
	if (strcmp(key, "compression-level") == 0) {
		if (value == NULL ||
		    !(value[0] >= '0' && value[0] <= '9') ||
		    value[1] != '\0') {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "Illeagal value `%s'",
			    value);
			return (ARCHIVE_FAILED);
		}
		xar->opt_compression_level = value[0] - '0';
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "toc-checksum") == 0) {
		if (value == NULL)
			xar->opt_toc_sumalg = CKSUM_NONE;
		else if (strcmp(value, "sha1") == 0)
			xar->opt_toc_sumalg = CKSUM_SHA1;
		else if (strcmp(value, "md5") == 0)
			xar->opt_toc_sumalg = CKSUM_MD5;
		else {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "Unknown checksum name: `%s'",
			    value);
			return (ARCHIVE_FAILED);
		}
		return (ARCHIVE_OK);
	}

	return (ARCHIVE_FAILED);
}