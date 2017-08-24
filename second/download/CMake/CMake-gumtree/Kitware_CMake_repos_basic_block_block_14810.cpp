(bytes_used > COMPRESSED_W_SIZE)
			memmove(a->compressed_buffer,
			    a->compressed_buffer + COMPRESSED_W_SIZE,
			    bytes_used);
		else
			memcpy(a->compressed_buffer,
			    a->compressed_buffer + COMPRESSED_W_SIZE,
			    bytes_used)