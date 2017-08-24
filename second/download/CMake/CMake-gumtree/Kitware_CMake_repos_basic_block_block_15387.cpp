(zip->entry_bytes_remaining > 0) {
		s = (size_t)zip->entry_bytes_remaining;
		if (s > a->null_length)
			s = a->null_length;
		r = _7z_write_data(a, a->nulls, s);
		if (r < 0)
			return ((int)r);
	}