(strcmp(key, "limit-dirs") == 0) {
			iso9660->opt.limit_dirs = value != NULL;
			return (ARCHIVE_OK);
		}