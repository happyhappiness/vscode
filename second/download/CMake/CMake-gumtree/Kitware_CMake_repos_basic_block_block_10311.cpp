{
		unsigned reqversion = archive_be16dec(p); p += 2;
		if (reqversion < 0x900) {
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC, "Invalid required version");
			return (ARCHIVE_FAILED);
		}
	}