				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Invalid Rockridge RE");
				return (NULL);
			}
			/*
			 * Sanity check: file does not have "CL" extension.
