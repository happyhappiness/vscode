(strcmp(name, "ea") == 0) {
			if (xattr_new(a, xar, list) != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			xar->xmlsts = FILE_EA;
		}