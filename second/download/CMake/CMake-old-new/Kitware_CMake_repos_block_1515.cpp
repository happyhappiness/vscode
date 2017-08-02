{
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "lz4 stream cheksum error");
				return (ARCHIVE_FATAL);
			}