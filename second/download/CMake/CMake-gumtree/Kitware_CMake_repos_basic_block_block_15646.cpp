(archive_entry_nlink(entry) < 2) {
		return (int)(++cpio->ino_next);
	}