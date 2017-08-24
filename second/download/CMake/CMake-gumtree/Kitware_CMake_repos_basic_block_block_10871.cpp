(zip->header_is_encoded == 0) {
		p = __archive_read_ahead(a, rbytes, NULL);
		if (p == NULL)
			return (NULL);
		zip->header_bytes_remaining -= rbytes;
		zip->pack_stream_bytes_unconsumed = rbytes;
	} else {
		const void *buff;
		ssize_t bytes;

		bytes = read_stream(a, &buff, rbytes, rbytes);
		if (bytes <= 0)
			return (NULL);
		zip->header_bytes_remaining -= bytes;
		p = buff;
	}