(run == ARCHIVE_Z_FINISH) {
		uint64_t bytes = sizeof(zip->wbuff) - zip->stream.avail_out;
		if (write_to_temp(a, zip->wbuff, (size_t)bytes) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		if ((zip->crc32flg & ENCODED_CRC32) && bytes)
			zip->encoded_crc32 = crc32(zip->encoded_crc32,
			    zip->wbuff, (unsigned)bytes);
	}