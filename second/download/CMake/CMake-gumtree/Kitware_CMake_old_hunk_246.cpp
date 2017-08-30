				archive_set_error(&a->archive,

				    ARCHIVE_ERRNO_MISC,

				    "Invalid Rockridge RE and CL");

				return (NULL);

			}

			/*

			 * Sanity check: The file type must be a directory.

