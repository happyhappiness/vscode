(a->tree != NULL && a->tree_enter_working_dir(a->tree) != 0) {
		archive_set_error(&a->archive, errno,
			    "Can't change dir to read extended attributes");
			return (ARCHIVE_FAILED);
	}