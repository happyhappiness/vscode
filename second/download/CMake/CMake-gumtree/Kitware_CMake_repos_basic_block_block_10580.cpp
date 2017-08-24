{
		__archive_read_consume(a, zip->pack_stream_bytes_unconsumed);
		zip->stream_offset += zip->pack_stream_bytes_unconsumed;
		zip->pack_stream_bytes_unconsumed = 0;
	}