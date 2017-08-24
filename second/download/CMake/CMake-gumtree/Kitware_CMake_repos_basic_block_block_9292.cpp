(best_bid_slot < 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "No formats registered");
		return (ARCHIVE_FATAL);
	}