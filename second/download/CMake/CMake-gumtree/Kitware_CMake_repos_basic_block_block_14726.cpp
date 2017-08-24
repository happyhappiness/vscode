(a->fd >= 0 && fstat(a->fd, &a->st) == 0) {
		a->pst = &a->st;
		return (ARCHIVE_OK);
	}