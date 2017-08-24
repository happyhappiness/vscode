{
		wintime -= EPOC_TIME;	/* 1970-01-01 00:00:00 (UTC) */
		if (ns != NULL)
			*ns = (long)(wintime % 10000000) * 100;
		return (wintime / 10000000);
	}