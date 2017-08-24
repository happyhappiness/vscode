{
			/*
			 * Couldn't open the entry, stat it or the on-disk type
			 * didn't match.  If this entry is optional, just
			 * ignore it and read the next header entry.
			 */
			*use_next = 1;
			return ARCHIVE_OK;
		}