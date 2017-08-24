(t == (time_t)-1) {
		archive_set_error(&(a->archive), EINVAL, "invalid date string");
		return (ARCHIVE_FAILED);
	}