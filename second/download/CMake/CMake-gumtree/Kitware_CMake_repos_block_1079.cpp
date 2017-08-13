{
				/* There is nothing more to read, fail */
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Missing format data");
				return (ARCHIVE_FATAL);
			}