{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Reading file truncated");
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		}