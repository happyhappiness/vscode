{
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Unsupported method");
		return (ARCHIVE_FAILED);
	}