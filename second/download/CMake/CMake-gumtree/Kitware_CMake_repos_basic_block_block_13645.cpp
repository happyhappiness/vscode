(strcmp(key, "mac-ext") == 0) {
		zip->process_mac_extensions = (val != NULL && val[0] != 0);
		return (ARCHIVE_OK);
	}