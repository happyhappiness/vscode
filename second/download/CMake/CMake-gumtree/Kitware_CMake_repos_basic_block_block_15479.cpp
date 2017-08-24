{
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