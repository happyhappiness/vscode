(csize < usize) {
		/* Store compressed size. */
		archive_be32enc(p + header_bytes + 4, (uint32_t)csize);
		r = __archive_write_filter(f->next_filter, data->compressed,
			header_bytes + block_info_bytes + csize);
	} else {
		/*
		 * This case, we output uncompressed data instead.
		 */
		/* Store uncompressed size as compressed size. */
		archive_be32enc(p + header_bytes + 4, (uint32_t)usize);
		r = __archive_write_filter(f->next_filter, data->compressed,
			header_bytes + block_info_bytes);
		if (r != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		r = __archive_write_filter(f->next_filter, data->uncompressed,
			usize);
	}