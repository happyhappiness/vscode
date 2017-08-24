{
		state->stage = READ_DEFAULT_STREAM;
		/* First, read a descriptor. */
		if((ret = lz4_filter_read_descriptor(self)) != ARCHIVE_OK)
			return (ret);
		state->stage = READ_DEFAULT_BLOCK;
	}