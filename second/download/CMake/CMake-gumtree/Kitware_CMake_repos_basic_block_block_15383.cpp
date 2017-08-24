{
	struct _7zip *zip = (struct _7zip *)a->format_data;
	int r;

	if (run == ARCHIVE_Z_FINISH && zip->stream.total_in == 0 && s == 0)
		return (0);

	if ((zip->crc32flg & PRECODE_CRC32) && s)
		zip->precode_crc32 = crc32(zip->precode_crc32, buff,
		    (unsigned)s);
	zip->stream.next_in = (const unsigned char *)buff;
	zip->stream.avail_in = s;
	for (;;) {
		/* Compress file data. */
		r = compression_code(&(a->archive), &(zip->stream), run);
		if (r != ARCHIVE_OK && r != ARCHIVE_EOF)
			return (ARCHIVE_FATAL);
		if (zip->stream.avail_out == 0) {
			if (write_to_temp(a, zip->wbuff, sizeof(zip->wbuff))
			    != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			zip->stream.next_out = zip->wbuff;
			zip->stream.avail_out = sizeof(zip->wbuff);
			if (zip->crc32flg & ENCODED_CRC32)
				zip->encoded_crc32 = crc32(zip->encoded_crc32,
				    zip->wbuff, sizeof(zip->wbuff));
			if (run == ARCHIVE_Z_FINISH && r != ARCHIVE_EOF)
				continue;
		}
		if (zip->stream.avail_in == 0)
			break;
	}
	if (run == ARCHIVE_Z_FINISH) {
		uint64_t bytes = sizeof(zip->wbuff) - zip->stream.avail_out;
		if (write_to_temp(a, zip->wbuff, (size_t)bytes) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		if ((zip->crc32flg & ENCODED_CRC32) && bytes)
			zip->encoded_crc32 = crc32(zip->encoded_crc32,
			    zip->wbuff, (unsigned)bytes);
	}

	return (s);
}