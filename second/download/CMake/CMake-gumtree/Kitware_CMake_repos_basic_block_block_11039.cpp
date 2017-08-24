{
			if (skipped >= 0) {
				archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
					"Truncated ar archive- failed consuming padding");
			}
			return (ARCHIVE_FATAL);
		}