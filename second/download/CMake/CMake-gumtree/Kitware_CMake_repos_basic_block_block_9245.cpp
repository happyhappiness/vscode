{
		/* Seek requests over 1GiB are broken down into
		 * multiple seeks.  This avoids overflows when the
		 * requests get passed through 32-bit arguments. */
		int64_t skip_limit = (int64_t)1 << 30;
		int64_t total = 0;
		for (;;) {
			int64_t get, ask = request;
			if (ask > skip_limit)
				ask = skip_limit;
			get = (self->archive->client.skipper)
				(&self->archive->archive, self->data, ask);
			total += get;
			if (get == 0 || get == request)
				return (total);
			if (get > request)
				return ARCHIVE_FATAL;
			request -= get;
		}
	}