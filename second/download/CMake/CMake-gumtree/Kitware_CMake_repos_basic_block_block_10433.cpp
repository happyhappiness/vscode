{
			free(ptr);
			archive_set_error(&self->archive->archive,
			    ENOMEM,
    			    "Can't allocate data for uudecode");
			return (ARCHIVE_FATAL);
		}