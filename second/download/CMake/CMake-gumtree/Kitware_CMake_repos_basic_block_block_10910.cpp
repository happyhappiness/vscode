{
			memmove(zip->uncompressed_buffer,
				zip->uncompressed_buffer + used,
				zip->uncompressed_buffer_bytes_remaining);
		}