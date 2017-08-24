(strcmp(key, "dironly") == 0) {
			mtree->dironly = (value != NULL)? 1: 0;
			return (ARCHIVE_OK);
		}