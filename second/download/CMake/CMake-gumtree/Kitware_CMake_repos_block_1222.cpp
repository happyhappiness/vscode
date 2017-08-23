{
			archive_set_error(&a->archive, errno,
			    "openat failed");
			return (ARCHIVE_FAILED);
		}