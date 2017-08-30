				archive_set_error(&a->archive,

				    ARCHIVE_ERRNO_MISC,

				    "Invalid Rockridge CL");

				goto fail;

			}

			/*

			 * Sanity check: The file type must be a regular file.

