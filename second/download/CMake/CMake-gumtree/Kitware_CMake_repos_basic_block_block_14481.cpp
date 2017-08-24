(strcmp(key, "timestamp") == 0) {
		data->timestamp = (value == NULL)?-1:1;
		return (ARCHIVE_OK);
	}