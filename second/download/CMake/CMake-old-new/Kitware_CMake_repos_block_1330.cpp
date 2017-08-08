{
			/* TODO: Should we seek offset of current file
			 * by bst ? */
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Illegal zisofs block pointers(cannot seek)");
			return (ARCHIVE_FATAL);
		}