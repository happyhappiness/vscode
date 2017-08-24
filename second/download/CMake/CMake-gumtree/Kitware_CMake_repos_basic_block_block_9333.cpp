{
			memset(a->bidders + i, 0, sizeof(a->bidders[0]));
			*bidder = (a->bidders + i);
			return (ARCHIVE_OK);
		}