{
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