(slash != NULL) {
		*slash = '\0';
		r = create_dir(a, path);
		*slash = '\\';
		if (r != ARCHIVE_OK)
			return (r);
	}