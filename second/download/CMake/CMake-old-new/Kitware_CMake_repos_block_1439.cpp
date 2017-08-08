{
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Lzip: CRC32 error");
		return (ARCHIVE_FAILED);
	}