(strcmp(pathname, ".") == 0) {
		archive_strcpy(&file->basename, ".");
		return (ARCHIVE_OK);
	}