{
			/* Non-ascii character is found. */
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "Insufficient compressed data");
			return (ARCHIVE_FATAL);
		}