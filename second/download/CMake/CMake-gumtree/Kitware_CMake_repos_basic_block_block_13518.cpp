((zip_entry->mode & AE_IFMT) == AE_IFIFO) {
		zip_entry->mode &= ~ AE_IFMT;
		zip_entry->mode |= AE_IFREG;
	}