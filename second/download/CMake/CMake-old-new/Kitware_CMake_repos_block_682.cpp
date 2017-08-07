{
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "A name buffer is too small");
			_isoent_free(isoent);
			return (ARCHIVE_FATAL);
		}