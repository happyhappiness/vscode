archive_set_error(&(self->archive->archive),
		    ARCHIVE_ERRNO_MISC,
		    "Failed to clean up %s compressor",
		    self->archive->archive.compression_name);