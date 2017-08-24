(pos == ARCHIVE_FAILED) {
				archive_set_error(&(a->archive),
				    ARCHIVE_ERRNO_MISC,
				    "Cannot seek.");
				return (ARCHIVE_FAILED);
			}