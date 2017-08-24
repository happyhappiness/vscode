{
		buffer_compressed[0] = 0xFF;/* uncompressed marker. */
		memcpy(buffer_compressed + 1, buff, size);
		bytes_compressed = size + 1;
	}