(r1 == ARCHIVE_EOF || r1 == ARCHIVE_FATAL) {
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		}