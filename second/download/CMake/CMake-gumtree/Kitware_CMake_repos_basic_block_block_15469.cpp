{
	uint8_t filetime[8];
	struct _7zip *zip = (struct _7zip *)a->format_data;
	struct file *file;
	int r;
	uint8_t b, mask;

	/*
	 * Make Time Bools.
	 */
	if (zip->total_number_time_defined[ti] == zip->total_number_entry) {
		/* Write Time Type. */
		r = enc_uint64(a, type);
		if (r < 0)
			return (r);
		/* Write EmptyStream Size. */
		r = enc_uint64(a, 2 + zip->total_number_entry * 8);
		if (r < 0)
			return (r);
		/* All are defined. */
		r = enc_uint64(a, 1);
		if (r < 0)
			return (r);
	} else {
		if (zip->total_number_time_defined[ti] == 0)
			return (ARCHIVE_OK);

		/* Write Time Type. */
		r = enc_uint64(a, type);
		if (r < 0)
			return (r);
		/* Write EmptyStream Size. */
		r = enc_uint64(a, 2 + ((zip->total_number_entry + 7) >> 3)
			+ zip->total_number_time_defined[ti] * 8);
		if (r < 0)
			return (r);

		/* All are not defined. */
		r = enc_uint64(a, 0);
		if (r < 0)
			return (r);

		b = 0;
		mask = 0x80;
		file = zip->file_list.first;
		for (;file != NULL; file = file->next) {
			if (file->flg & flg)
				b |= mask;
			mask >>= 1;
			if (mask == 0) {
				r = (int)compress_out(a, &b, 1, ARCHIVE_Z_RUN);
				if (r < 0)
					return (r);
				mask = 0x80;
				b = 0;
			}
		}
		if (mask != 0x80) {
			r = (int)compress_out(a, &b, 1, ARCHIVE_Z_RUN);
			if (r < 0)
				return (r);
		}
	}

	/* External. */
	r = enc_uint64(a, 0);
	if (r < 0)
		return (r);


	/*
	 * Make Times.
	 */
	file = zip->file_list.first;
	for (;file != NULL; file = file->next) {
		if ((file->flg & flg) == 0)
			continue;
		archive_le64enc(filetime, utcToFiletime(file->times[ti].time,
			file->times[ti].time_ns));
		r = (int)compress_out(a, filetime, 8, ARCHIVE_Z_RUN);
		if (r < 0)
			return (r);
	}

	return (ARCHIVE_OK);
}