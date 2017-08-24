{
		ssize_t bytes_avail;

		d = __archive_read_ahead(a, cfdata->compressed_bytes_remaining,
		    &bytes_avail);
		if (bytes_avail <= 0) {
			*avail = truncated_error(a);
			return (NULL);
		}
		cfdata->unconsumed = cfdata->compressed_bytes_remaining;
		cfdata->sum_ptr = d;
		if (cab_minimum_consume_cfdata(a, cfdata->unconsumed) < 0) {
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
	}