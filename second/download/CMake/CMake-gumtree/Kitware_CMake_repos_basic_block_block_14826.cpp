(bytes_to_write == MAX_DECMPFS_BLOCK_SIZE)
		buffer_to_write = buff;
	else {
		memcpy(a->uncompressed_buffer +
		    MAX_DECMPFS_BLOCK_SIZE - a->block_remaining_bytes,
		    buff, bytes_to_write);
		buffer_to_write = a->uncompressed_buffer;
	}