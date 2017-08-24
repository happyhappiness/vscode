{
		xar->stream.total_in = 0;
		xar->stream.next_out = xar->wbuff;
		xar->stream.avail_out = sizeof(xar->wbuff);
		xar->stream.total_out = 0;
	}