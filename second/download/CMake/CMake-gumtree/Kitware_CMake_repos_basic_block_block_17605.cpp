(strcmp(key, "zip64") == 0) {
		/*
		 * Bias decisions about Zip64: force them to be
		 * generated in certain cases where they are not
		 * forbidden or avoid them in certain cases where they
		 * are not strictly required.
		 */
		if (val != NULL && *val != '\0') {
			zip->flags |= ZIP_FLAG_FORCE_ZIP64;
			zip->flags &= ~ZIP_FLAG_AVOID_ZIP64;
		} else {
			zip->flags &= ~ZIP_FLAG_FORCE_ZIP64;
			zip->flags |= ZIP_FLAG_AVOID_ZIP64;
		}
		return (ARCHIVE_OK);
	}