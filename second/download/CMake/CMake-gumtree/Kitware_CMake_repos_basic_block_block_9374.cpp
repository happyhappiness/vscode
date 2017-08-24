(filter->skip != NULL) {
		bytes_skipped = (filter->skip)(filter, request);
		if (bytes_skipped < 0) {	/* error */
			filter->fatal = 1;
			return (bytes_skipped);
		}
		filter->position += bytes_skipped;
		total_bytes_skipped += bytes_skipped;
		request -= bytes_skipped;
		if (request == 0)
			return (total_bytes_skipped);
	}