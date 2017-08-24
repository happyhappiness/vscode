{
		free(out_block);
		free(state);
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for gzip decompression");
		return (ARCHIVE_FATAL);
	}