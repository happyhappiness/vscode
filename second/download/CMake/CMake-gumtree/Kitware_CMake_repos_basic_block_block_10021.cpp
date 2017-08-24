((fileAttributes & FILE_ATTRIBUTE_SPARSE_FILE) == 0) {
		if (fd < 0)
			CloseHandle(h);
		return (ARCHIVE_OK);
	}