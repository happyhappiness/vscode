{
			archive_set_error(a, errno,
			    "Failed to open '%S'", wfilename);
			return (ARCHIVE_FATAL);
		}