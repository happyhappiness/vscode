{
		/* Packed mode. */
		if (minimum > zip->uncompressed_buffer_bytes_remaining) {
			/*
			 * If remaining uncompressed data size is less than
			 * the minimum size, fill the buffer up to the
			 * minimum size.
			 */
			if (extract_pack_stream(a, minimum) < 0)
				return (ARCHIVE_FATAL);
		}
		if (size > zip->uncompressed_buffer_bytes_remaining)
			bytes_avail = (ssize_t)
			    zip->uncompressed_buffer_bytes_remaining;
		else
			bytes_avail = (ssize_t)size;
		*buff = zip->uncompressed_buffer_pointer;
		zip->uncompressed_buffer_pointer += bytes_avail;
	}