{
	struct _7zip *zip = (struct _7zip *)a->format_data;
	struct file *file;
	int r;
	uint8_t b, mask;

	/*
	 * Make FilesInfo.
	 */
	r = enc_uint64(a, kHeader);
	if (r < 0)
		return (r);

	/*
	 * If there are empty files only, do not write MainStreamInfo.
	 */
	if (zip->total_number_nonempty_entry) {
		/*
		 * Make MainStreamInfo.
		 */
		r = enc_uint64(a, kMainStreamsInfo);
		if (r < 0)
			return (r);
		r = make_streamsInfo(a, offset, pack_size, unpack_size,
		      codernum, coders, 1, 0);
		if (r < 0)
			return (r);
	}

	/*
	 * Make FilesInfo.
	 */
	r = enc_uint64(a, kFilesInfo);
	if (r < 0)
		return (r);

	/* Write numFiles. */
	r = enc_uint64(a, zip->total_number_entry);
	if (r < 0)
		return (r);

	if (zip->total_number_empty_entry > 0) {
		/* Make EmptyStream. */
		r = enc_uint64(a, kEmptyStream);
		if (r < 0)
			return (r);

		/* Write EmptyStream Size. */
		r = enc_uint64(a, (zip->total_number_entry+7)>>3);
		if (r < 0)
			return (r);

		b = 0;
		mask = 0x80;
		file = zip->file_list.first;
		for (;file != NULL; file = file->next) {
			if (file->size == 0)
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

	if (zip->total_number_empty_entry > zip->total_number_dir_entry) {
		/* Make EmptyFile. */
		r = enc_uint64(a, kEmptyFile);
		if (r < 0)
			return (r);

		/* Write EmptyFile Size. */
		r = enc_uint64(a, (zip->total_number_empty_entry + 7) >> 3);
		if (r < 0)
			return (r);

		b = 0;
		mask = 0x80;
		file = zip->file_list.first;
		for (;file != NULL; file = file->next) {
			if (file->size)
				continue;
			if (!file->dir)
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

	/* Make Name. */
	r = enc_uint64(a, kName);
	if (r < 0)
		return (r);

	/* Write Name size. */
	r = enc_uint64(a, zip->total_bytes_entry_name+1);
	if (r < 0)
		return (r);

	/* Write dmy byte. */
	r = enc_uint64(a, 0);
	if (r < 0)
		return (r);

	file = zip->file_list.first;
	for (;file != NULL; file = file->next) {
		r = (int)compress_out(a, file->utf16name, file->name_len+2,
			ARCHIVE_Z_RUN);
		if (r < 0)
			return (r);
	}

	/* Make MTime. */
	r = make_time(a, kMTime, MTIME_IS_SET, MTIME);
	if (r < 0)
		return (r);

	/* Make CTime. */
	r = make_time(a, kCTime, CTIME_IS_SET, CTIME);
	if (r < 0)
		return (r);

	/* Make ATime. */
	r = make_time(a, kATime, ATIME_IS_SET, ATIME);
	if (r < 0)
		return (r);

	/* Make Attributes. */
	r = enc_uint64(a, kAttributes);
	if (r < 0)
		return (r);

	/* Write Attributes size. */
	r = enc_uint64(a, 2 + zip->total_number_entry * 4);
	if (r < 0)
		return (r);

	/* Write "All Are Defined". */
	r = enc_uint64(a, 1);
	if (r < 0)
		return (r);

	/* Write dmy byte. */
	r = enc_uint64(a, 0);
	if (r < 0)
		return (r);

	file = zip->file_list.first;
	for (;file != NULL; file = file->next) {
		/*
		 * High 16bits is unix mode.
		 * Low 16bits is Windows attributes.
		 */
		uint32_t encattr, attr;
		if (file->dir)
			attr = 0x8010;
		else
			attr = 0x8020;
		if ((file->mode & 0222) == 0)
			attr |= 1;/* Read Only. */
		attr |= ((uint32_t)file->mode) << 16;
		archive_le32enc(&encattr, attr);
		r = (int)compress_out(a, &encattr, 4, ARCHIVE_Z_RUN);
		if (r < 0)
			return (r);
	}

	/* Write End. */
	r = enc_uint64(a, kEnd);
	if (r < 0)
		return (r);

	/* Write End. */
	r = enc_uint64(a, kEnd);
	if (r < 0)
		return (r);

	return (ARCHIVE_OK);
}