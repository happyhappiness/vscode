{
	struct private_data *state = (struct private_data *)self->data;
	const char *read_buf;
	ssize_t bytes_remaining;
	ssize_t descriptor_bytes;
	unsigned char flag, bd;
	unsigned int chsum, chsum_verifier;

	/* Make sure we have 2 bytes for flags. */
	read_buf = __archive_read_filter_ahead(self->upstream, 2,
	    &bytes_remaining);
	if (read_buf == NULL) {
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC,
		    "truncated lz4 input");
		return (ARCHIVE_FATAL);
	}

	/*
	   Parse flags.
	 */
	flag = (unsigned char)read_buf[0];
	/* Verify version number. */
	if ((flag & 0xc0) != 1<<6)
		goto malformed_error;
	/* A reserved bit must be zero. */
	if (flag & 0x02)
		goto malformed_error;
	state->flags.block_independence = (flag & 0x20) != 0;
	state->flags.block_checksum = (flag & 0x10)?4:0;
	state->flags.stream_size = (flag & 0x08) != 0;
	state->flags.stream_checksum = (flag & 0x04) != 0;
	state->flags.preset_dictionary = (flag & 0x01) != 0;

	/* BD */
	bd = (unsigned char)read_buf[1];
	/* Reserved bits must be zero. */
	if (bd & 0x8f)
		goto malformed_error;
	/* Get a maximum block size. */
	switch (read_buf[1] >> 4) {
	case 4: /* 64 KB */
		state->flags.block_maximum_size = 64 * 1024;
		break;
	case 5: /* 256 KB */
		state->flags.block_maximum_size = 256 * 1024;
		break;
	case 6: /* 1 MB */
		state->flags.block_maximum_size = 1024 * 1024;
		break;
	case 7: /* 4 MB */
		state->flags.block_maximum_size = 4 * 1024 * 1024;
		break;
	default:
		goto malformed_error;
	}

	/* Read the whole descriptor in a stream block. */
	descriptor_bytes = 3;
	if (state->flags.stream_size)
		descriptor_bytes += 8;
	if (state->flags.preset_dictionary)
		descriptor_bytes += 4;
	if (bytes_remaining < descriptor_bytes) {
		read_buf = __archive_read_filter_ahead(self->upstream,
		    descriptor_bytes, &bytes_remaining);
		if (read_buf == NULL) {
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "truncated lz4 input");
			return (ARCHIVE_FATAL);
		}
	}
	/* Check if a descriptor is corrupted */
	chsum = __archive_xxhash.XXH32(read_buf, (int)descriptor_bytes -1, 0);
	chsum = (chsum >> 8) & 0xff;
	chsum_verifier = read_buf[descriptor_bytes-1] & 0xff;
	if (chsum != chsum_verifier)
		goto malformed_error;

	__archive_read_filter_consume(self->upstream, descriptor_bytes);

	/* Make sure we have an enough buffer for uncompressed data. */
	if (lz4_allocate_out_block(self) != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	if (state->flags.stream_checksum)
		state->xxh32_state = __archive_xxhash.XXH32_init(0);

	state->decoded_size = 0;
	/* Success */
	return (ARCHIVE_OK);
malformed_error:
	archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
	    "malformed lz4 data");
	return (ARCHIVE_FATAL);
}