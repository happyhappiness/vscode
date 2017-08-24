{
		iso9660->wbuff_remaining -= nw;
		memmove(iso9660->wbuff, iso9660->wbuff + wsize - nw, nw);
	}