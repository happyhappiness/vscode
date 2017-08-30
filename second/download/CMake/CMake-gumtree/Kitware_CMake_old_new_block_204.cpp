{
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for lzma decompression");
		free(out_block);
		free(state);
		return (ARCHIVE_FATAL);
	}