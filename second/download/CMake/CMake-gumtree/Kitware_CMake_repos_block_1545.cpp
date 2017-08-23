{
	struct private_data *state = (struct private_data *)self->data;
	ssize_t compressed_size;
	const char *read_buf;
	ssize_t bytes_remaining;
	int checksum_size;
	ssize_t uncompressed_size;
	size_t prefix64k;

	*p = NULL;

	/* Make sure we have 4 bytes for a block size. */
	read_buf = __archive_read_filter_ahead(self->upstream, 4,
	    &bytes_remaining);
	if (read_buf == NULL)
		goto truncated_error;
	compressed_size = archive_le32dec(read_buf);
	if ((compressed_size & ~(1 << 31)) > state->flags.block_maximum_size)
		goto malformed_error;
	/* A compressed size == 0 means the end of stream blocks. */
	if (compressed_size == 0) {
		__archive_read_filter_consume(self->upstream, 4);
		return 0;
	}

	checksum_size = state->flags.block_checksum;
	/* Check if the block is uncompressed. */
	if (compressed_size & (1 << 31)) {
		compressed_size &= ~(1 << 31);
		uncompressed_size = compressed_size;
	} else
		uncompressed_size = 0;/* Unknown yet. */

	/*
	  Unfortunately, lz4 decompression API requires a whole block
	  for its decompression speed, so we read a whole block and allocate
	  a huge buffer used for decoded data.
	*/
	read_buf = __archive_read_filter_ahead(self->upstream,
	    4 + compressed_size + checksum_size, &bytes_remaining);
	if (read_buf == NULL)
		goto truncated_error;

	/* Optional process, checking a block sum. */
	if (checksum_size) {
		unsigned int chsum = __archive_xxhash.XXH32(
			read_buf + 4, (int)compressed_size, 0);
		unsigned int chsum_block =
		    archive_le32dec(read_buf + 4 + compressed_size);
		if (chsum != chsum_block)
			goto malformed_error;
	}


	/* If the block is uncompressed, there is nothing to do. */
	if (uncompressed_size) {
		/* Prepare a prefix 64k block for next block. */
		if (!state->flags.block_independence) {
			prefix64k = 64 * 1024;
			if (uncompressed_size < (ssize_t)prefix64k) {
				memcpy(state->out_block
					+ prefix64k - uncompressed_size,
				    read_buf + 4,
				    uncompressed_size);
				memset(state->out_block, 0,
				    prefix64k - uncompressed_size);
			} else {
				memcpy(state->out_block,
				    read_buf + 4
					+ uncompressed_size - prefix64k,
				    prefix64k);
			}
			state->decoded_size = 0;
		}
		state->unconsumed = 4 + uncompressed_size + checksum_size;
		*p = read_buf + 4;
		return uncompressed_size;
	}

	/*
	   Decompress a block data.
	 */
	if (state->flags.block_independence) {
		prefix64k = 0;
		uncompressed_size = LZ4_decompress_safe(read_buf + 4,
		    state->out_block, (int)compressed_size,
		    state->flags.block_maximum_size);
	} else {
		prefix64k = 64 * 1024;
		if (state->decoded_size) {
			if (state->decoded_size < prefix64k) {
				memmove(state->out_block
					+ prefix64k - state->decoded_size,
				    state->out_block + prefix64k,
				    state->decoded_size);
				memset(state->out_block, 0,
				    prefix64k - state->decoded_size);
			} else {
				memmove(state->out_block,
				    state->out_block + state->decoded_size,
				    prefix64k);
			}
		}
#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
		uncompressed_size = LZ4_decompress_safe_usingDict(
		    read_buf + 4,
		    state->out_block + prefix64k, (int)compressed_size,
		    state->flags.block_maximum_size,
		    state->out_block,
		    prefix64k);
#else
		uncompressed_size = LZ4_decompress_safe_withPrefix64k(
		    read_buf + 4,
		    state->out_block + prefix64k, (int)compressed_size,
		    state->flags.block_maximum_size);
#endif
	}

	/* Check if an error occurred in the decompression process. */
	if (uncompressed_size < 0) {
		archive_set_error(&(self->archive->archive),
		    ARCHIVE_ERRNO_MISC, "lz4 decompression failed");
		return (ARCHIVE_FATAL);
	}

	state->unconsumed = 4 + compressed_size + checksum_size;
	*p = state->out_block + prefix64k;
	state->decoded_size = uncompressed_size;
	return uncompressed_size;

malformed_error:
	archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
	    "malformed lz4 data");
	return (ARCHIVE_FATAL);
truncated_error:
	archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
	    "truncated lz4 input");
	return (ARCHIVE_FATAL);
}