(strcmp(key, "experimental") == 0) {
		if (val == NULL || val[0] == 0) {
			zip->flags &= ~ ZIP_FLAG_EXPERIMENT_EL;
		} else {
			zip->flags |= ZIP_FLAG_EXPERIMENT_EL;
		}
		return (ARCHIVE_OK);
	}