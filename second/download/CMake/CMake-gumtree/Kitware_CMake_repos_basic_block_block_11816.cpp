((file->mode & AE_IFMT) != AE_IFREG || file->number == -1)
		return (ARCHIVE_OK);