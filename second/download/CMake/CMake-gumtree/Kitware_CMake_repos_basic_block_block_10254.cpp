{
	struct private_data *state = (struct private_data *)self->data;
	ssize_t ret;

	if (state->eof) {
		*p = NULL;
		return (0);
	}

	__archive_read_filter_consume(self->upstream, state->unconsumed);
	state->unconsumed = 0;

	switch (state->stage) {
	case SELECT_STREAM:
		break;
	case READ_DEFAULT_STREAM:
	case READ_LEGACY_STREAM:
		/* Reading a lz4 stream already failed. */
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC, "Invalid sequence.");
		return (ARCHIVE_FATAL);
	case READ_DEFAULT_BLOCK:
		ret = lz4_filter_read_default_stream(self, p);
		if (ret != 0 || state->stage != SELECT_STREAM)
			return ret;
		break;
	case READ_LEGACY_BLOCK:
		ret = lz4_filter_read_legacy_stream(self, p);
		if (ret != 0 || state->stage != SELECT_STREAM)
			return ret;
		break;
	default:
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC, "Program error.");
		return (ARCHIVE_FATAL);
		break;
	}

	while (state->stage == SELECT_STREAM) {
		const char *read_buf;

		/* Read a magic number. */
		read_buf = __archive_read_filter_ahead(self->upstream, 4,
				NULL);
		if (read_buf == NULL) {
			state->eof = 1;
			*p = NULL;
			return (0);
		}
		uint32_t number = archive_le32dec(read_buf);
		__archive_read_filter_consume(self->upstream, 4);
		if (number == LZ4_MAGICNUMBER)
			return lz4_filter_read_default_stream(self, p);
		else if (number == LZ4_LEGACY)
			return lz4_filter_read_legacy_stream(self, p);
		else if ((number & ~0xF) == LZ4_SKIPPABLED) {
			read_buf = __archive_read_filter_ahead(
				self->upstream, 4, NULL);
			if (read_buf == NULL) {
				archive_set_error(
				    &self->archive->archive,
		    		    ARCHIVE_ERRNO_MISC,
				    "Malformed lz4 data");
				return (ARCHIVE_FATAL);
			}
			uint32_t skip_bytes = archive_le32dec(read_buf);
			__archive_read_filter_consume(self->upstream,
				4 + skip_bytes);
		} else {
			/* Ignore following unrecognized data. */
			state->eof = 1;
			*p = NULL;
			return (0);
		}
	}
	state->eof = 1;
	*p = NULL;
	return (0);
}