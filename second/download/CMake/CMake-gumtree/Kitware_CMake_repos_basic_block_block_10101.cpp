(fstat(fd, &st) != 0) {
		if (mine->filename_type == FNT_WCS)
			archive_set_error(a, errno, "Can't stat '%S'",
			    wfilename);
		else
			archive_set_error(a, errno, "Can't stat '%s'",
			    filename);
		goto fail;
	}