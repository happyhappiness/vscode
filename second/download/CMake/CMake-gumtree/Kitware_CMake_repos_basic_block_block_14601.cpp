(child == -1) {
		archive_set_error(f->archive, EINVAL,
		    "Can't launch external program: %s", cmd);
		return (ARCHIVE_FATAL);
	}