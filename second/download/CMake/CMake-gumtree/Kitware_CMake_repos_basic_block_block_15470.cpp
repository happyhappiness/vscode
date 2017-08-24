(;file != NULL; file = file->next) {
		if ((file->flg & flg) == 0)
			continue;
		archive_le64enc(filetime, utcToFiletime(file->times[ti].time,
			file->times[ti].time_ns));
		r = (int)compress_out(a, filetime, 8, ARCHIVE_Z_RUN);
		if (r < 0)
			return (r);
	}