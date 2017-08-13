{
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for bzip2 decompression");
		free(out_block);
		free(state);
		return (ARCHIVE_FATAL);
	}