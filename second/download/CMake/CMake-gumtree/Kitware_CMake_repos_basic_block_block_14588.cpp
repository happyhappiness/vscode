{
			memcpy(data->uncompressed
				+ data->uncompressed_buffer_size
				- data->uncompressed_avail_bytes,
			    p, length);
			data->uncompressed_avail_bytes -= length;
			return (ARCHIVE_OK);
		}