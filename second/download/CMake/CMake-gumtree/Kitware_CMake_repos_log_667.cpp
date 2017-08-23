archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library: "
		    " Zlib error %d", ret);