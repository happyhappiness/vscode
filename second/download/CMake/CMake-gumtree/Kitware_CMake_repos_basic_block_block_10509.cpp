(f == NULL || avail_in < tail) {
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Lzip: Remaining data is less bytes");
		return (ARCHIVE_FAILED);
	}