{
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
	}