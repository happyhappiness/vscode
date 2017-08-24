(isofile_gen_utility_names(a, file) < ARCHIVE_WARN) {
		isofile_free(file);
		return (NULL);
	}