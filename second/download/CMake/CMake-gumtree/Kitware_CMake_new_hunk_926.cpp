#endif
	}
	if (fstat(fd, &st) != 0) {
		if (mine->filename_type == FNT_WCS)
			archive_set_error(a, errno, "Can't stat '%S'",
			    wfilename);
		else
