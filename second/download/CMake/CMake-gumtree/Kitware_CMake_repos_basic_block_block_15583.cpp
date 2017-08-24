{
		zip->stream.total_in = 0;
		zip->stream.next_out = zip->wbuff;
		zip->stream.avail_out = sizeof(zip->wbuff);
		zip->stream.total_out = 0;
	}