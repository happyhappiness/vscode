{
						archive_set_error(
						    &self->archive->archive,
						    ARCHIVE_ERRNO_FILE_FORMAT,
						    "Unrecoginized rpm header");
						return (ARCHIVE_FATAL);
					}