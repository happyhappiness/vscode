{
	struct _7zip *zip = (struct _7zip *)a->format_data;
	struct file *file;
	int r;

	/*
	 * Make SubStreamsInfo.
	 */
	r = enc_uint64(a, kSubStreamsInfo);
	if (r < 0)
		return (r);

	if (zip->total_number_nonempty_entry > 1 && coders->codec != _7Z_COPY) {
		/*
		 * Make NumUnPackStream.
		 */
		r = enc_uint64(a, kNumUnPackStream);
		if (r < 0)
			return (r);

		/* Write numUnpackStreams */
		r = enc_uint64(a, zip->total_number_nonempty_entry);
		if (r < 0)
			return (r);

		/*
		 * Make kSize.
		 */
		r = enc_uint64(a, kSize);
		if (r < 0)
			return (r);
		file = zip->file_list.first;
		for (;file != NULL; file = file->next) {
			if (file->next == NULL ||
			    file->next->size == 0)
				break;
			r = enc_uint64(a, file->size);
			if (r < 0)
				return (r);
		}
	}

	/*
	 * Make CRC.
	 */
	r = enc_uint64(a, kCRC);
	if (r < 0)
		return (r);


	/* All are defined */
	r = enc_uint64(a, 1);
	if (r < 0)
		return (r);
	file = zip->file_list.first;
	for (;file != NULL; file = file->next) {
		uint8_t crc[4];
		if (file->size == 0)
			break;
		archive_le32enc(crc, file->crc32);
		r = (int)compress_out(a, crc, 4, ARCHIVE_Z_RUN);
		if (r < 0)
			return (r);
	}

	/* Write End. */
	r = enc_uint64(a, kEnd);
	if (r < 0)
		return (r);
	return (ARCHIVE_OK);
}