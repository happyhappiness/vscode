{
	int64_t ino = archive_entry_ino64(entry);
	int ino_new;
	size_t i;

	/*
	 * If no index number was given, don't assign one.  In
	 * particular, this handles the end-of-archive marker
	 * correctly by giving it a zero index value.  (This is also
	 * why we start our synthetic index numbers with one below.)
	 */
	if (ino == 0)
		return (0);

	/* Don't store a mapping if we don't need to. */
	if (archive_entry_nlink(entry) < 2) {
		return (int)(++cpio->ino_next);
	}

	/* Look up old ino; if we have it, this is a hardlink
	 * and we reuse the same value. */
	for (i = 0; i < cpio->ino_list_next; ++i) {
		if (cpio->ino_list[i].old == ino)
			return (cpio->ino_list[i].new);
	}

	/* Assign a new index number. */
	ino_new = (int)(++cpio->ino_next);

	/* Ensure space for the new mapping. */
	if (cpio->ino_list_size <= cpio->ino_list_next) {
		size_t newsize = cpio->ino_list_size < 512
		    ? 512 : cpio->ino_list_size * 2;
		void *newlist = realloc(cpio->ino_list,
		    sizeof(cpio->ino_list[0]) * newsize);
		if (newlist == NULL)
			return (-1);

		cpio->ino_list_size = newsize;
		cpio->ino_list = newlist;
	}

	/* Record and return the new value. */
	cpio->ino_list[cpio->ino_list_next].old = ino;
	cpio->ino_list[cpio->ino_list_next].new = ino_new;
	++cpio->ino_list_next;
	return (ino_new);
}