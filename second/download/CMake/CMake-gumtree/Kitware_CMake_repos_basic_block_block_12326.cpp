(strcmp(key, "nochange") == 0) {
		*parsed_kws |= MTREE_HAS_NOCHANGE;
		return (ARCHIVE_OK);
	}