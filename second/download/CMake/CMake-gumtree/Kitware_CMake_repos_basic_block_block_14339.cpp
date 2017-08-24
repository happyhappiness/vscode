(f->write == NULL)
		/* If unset, a fatal error has already occurred, so this filter
		 * didn't open. We cannot write anything. */
		return(ARCHIVE_FATAL);