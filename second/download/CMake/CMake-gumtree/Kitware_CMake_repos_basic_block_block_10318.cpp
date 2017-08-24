(flags & (CRC32_UNCOMPRESSED | ADLER32_UNCOMPRESSED)) {
		p = __archive_read_filter_ahead(self->upstream, 4, NULL);
		if (p == NULL)
			goto truncated;
		state->compressed_cksum = state->uncompressed_cksum =
		    archive_be32dec(p);
		__archive_read_filter_consume(self->upstream, 4);
	}