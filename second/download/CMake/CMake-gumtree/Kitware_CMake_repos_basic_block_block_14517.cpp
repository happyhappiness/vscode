(strcmp(key, "block-dependence") == 0) {
		data->block_independence = value == NULL;
		return (ARCHIVE_OK);
	}