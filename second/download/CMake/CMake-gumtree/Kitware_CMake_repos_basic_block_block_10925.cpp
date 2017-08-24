(zip->stream_offset != pack_offset) {
		if (0 > __archive_read_seek(a, pack_offset + zip->seek_base,
		    SEEK_SET))
			return (ARCHIVE_FATAL);
		zip->stream_offset = pack_offset;
	}