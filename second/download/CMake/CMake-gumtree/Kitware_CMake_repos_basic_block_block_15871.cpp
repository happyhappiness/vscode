(iso9660->bytes_remaining > 0) {
		size_t s;

		s = (iso9660->bytes_remaining > a->null_length)?
		    a->null_length: (size_t)iso9660->bytes_remaining;
		if (write_iso9660_data(a, a->nulls, s) < 0)
			return (ARCHIVE_FATAL);
		iso9660->bytes_remaining -= s;
	}