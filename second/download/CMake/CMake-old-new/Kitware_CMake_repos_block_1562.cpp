{
			/* We couldn't get the symlink-name. */
			archive_set_error(&a->archive,
		    	    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Unknown symlink-name");
			archive_string_free(&pathname);
			archive_string_free(&linkname);
			return (ARCHIVE_FAILED);
		}