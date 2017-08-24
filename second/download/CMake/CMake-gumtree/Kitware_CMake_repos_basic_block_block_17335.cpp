{
		int algsize;
		xar->temp_offset = 0;
		xar->temp_fd = __archive_mktemp(NULL);
		if (xar->temp_fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Couldn't create temporary file");
			return (ARCHIVE_FATAL);
		}
		algsize = getalgsize(xar->opt_toc_sumalg);
		if (algsize > 0) {
			if (lseek(xar->temp_fd, algsize, SEEK_SET) < 0) {
				archive_set_error(&(a->archive), errno,
				    "lseek failed");
				return (ARCHIVE_FATAL);
			}
			xar->temp_offset = algsize;
		}
	}