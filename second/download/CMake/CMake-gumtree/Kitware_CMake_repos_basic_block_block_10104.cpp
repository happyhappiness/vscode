{
			archive_set_error(a, errno,
			    "Failed to open '%s'", filename);
			return (ARCHIVE_FATAL);
		}