(i = 0; i < slots; i++, a->format++) {
		if (a->format->bid) {
			bid = (a->format->bid)(a, best_bid);
			if (bid == ARCHIVE_FATAL)
				return (ARCHIVE_FATAL);
			if (a->filter->position != 0)
				__archive_read_seek(a, 0, SEEK_SET);
			if ((bid > best_bid) || (best_bid_slot < 0)) {
				best_bid = bid;
				best_bid_slot = i;
			}
		}
	}