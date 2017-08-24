((flags & (CRC32_COMPRESSED | ADLER32_COMPRESSED)) &&
	    state->compressed_size < state->uncompressed_size) {
		p = __archive_read_filter_ahead(self->upstream, 4, NULL);
		if (p == NULL)
			goto truncated;
		state->compressed_cksum = archive_be32dec(p);
		__archive_read_filter_consume(self->upstream, 4);
	}