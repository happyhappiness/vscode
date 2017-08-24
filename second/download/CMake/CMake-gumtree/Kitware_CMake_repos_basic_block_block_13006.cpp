{
	eof:
		/* it's our lucky day, no work, we can leave early */
		*buf = NULL;
		*bsz = 0U;
		*off = w->cntoff + 4U/*for \r\n\r\n separator*/;
		w->unconsumed = 0U;
		return (ARCHIVE_EOF);
	}