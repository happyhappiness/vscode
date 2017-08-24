{
		const void *buff;
		ssize_t bytes;

		bytes = read_stream(a, &buff, rbytes, rbytes);
		if (bytes <= 0)
			return (NULL);
		zip->header_bytes_remaining -= bytes;
		p = buff;
	}