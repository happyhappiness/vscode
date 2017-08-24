(r != ARCHIVE_OK) {
			/* If a write fails, we're pretty much toast. */
			return (ARCHIVE_FATAL);
		}