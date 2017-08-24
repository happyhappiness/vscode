(a->flags & ARCHIVE_EXTRACT_SECURE_SYMLINKS) {
		ret = check_symlinks(a);
		if (ret != ARCHIVE_OK)
			return (ret);
	}