{
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC, "Corrupted data");
		return (ARCHIVE_FATAL);
	}