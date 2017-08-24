{
		bidder = filter->bidder;
		if (bidder == NULL)
			continue;
		if (bidder->options == NULL)
			/* This bidder does not support option */
			continue;
		if (m != NULL) {
			if (strcmp(filter->name, m) != 0)
				continue;
			++matched_modules;
		}

		r = bidder->options(bidder, o, v);

		if (r == ARCHIVE_FATAL)
			return (ARCHIVE_FATAL);

		if (r == ARCHIVE_OK)
			rv = ARCHIVE_OK;
	}