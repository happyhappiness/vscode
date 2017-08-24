(strcmp(key, "stream-checksum") == 0) {
		data->stream_checksum = value != NULL;
		return (ARCHIVE_OK);
	}