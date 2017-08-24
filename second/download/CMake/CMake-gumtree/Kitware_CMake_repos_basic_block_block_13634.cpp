(AE_IFREG != (zip->entry->mode & AE_IFMT))
		return (ARCHIVE_EOF);