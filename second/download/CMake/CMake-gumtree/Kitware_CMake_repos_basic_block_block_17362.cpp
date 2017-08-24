(xar->bytes_remaining > 0) {
		s = (size_t)xar->bytes_remaining;
		if (s > a->null_length)
			s = a->null_length;
		w = xar_write_data(a, a->nulls, s);
		if (w > 0)
			xar->bytes_remaining -= w;
		else
			return (w);
	}