{
		/* An invalid code is a fatal error. */
		archive_set_error(&(self->archive->archive), -1,
		    "Invalid compressed data");
		return (ARCHIVE_FATAL);
	}