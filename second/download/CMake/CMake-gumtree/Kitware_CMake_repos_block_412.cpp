{
			archive_set_error(&(a->archive), 0,
			    "Truncated 7-Zip archive");
			return (ARCHIVE_FATAL);
		}