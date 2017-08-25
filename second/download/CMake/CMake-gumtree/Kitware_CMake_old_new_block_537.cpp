{
			/* NOTE: If the last argument is NULL, this will
			 * fail only by memeory allocation failure. */
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Symlink");
			return (ARCHIVE_FATAL);
		}