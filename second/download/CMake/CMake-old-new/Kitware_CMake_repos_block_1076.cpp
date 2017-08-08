{
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for uudecode");
		free(uudecode);
		free(out_buff);
		free(in_buff);
		return (ARCHIVE_FATAL);
	}