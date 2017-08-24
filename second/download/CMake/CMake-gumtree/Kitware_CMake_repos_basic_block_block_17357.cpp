(xar->cur_file->data.compression == NONE) {
		checksum_update(&(xar->e_sumwrk), buff, s);
		checksum_update(&(xar->a_sumwrk), buff, s);
		size = rsize = s;
	} else {
		xar->stream.next_in = (const unsigned char *)buff;
		xar->stream.avail_in = s;
		if (xar->bytes_remaining > s)
			run = ARCHIVE_Z_RUN;
		else
			run = ARCHIVE_Z_FINISH;
		/* Compress file data. */
		r = compression_code(&(a->archive), &(xar->stream), run);
		if (r != ARCHIVE_OK && r != ARCHIVE_EOF)
			return (ARCHIVE_FATAL);
		rsize = s - xar->stream.avail_in;
		checksum_update(&(xar->e_sumwrk), buff, rsize);
		size = sizeof(xar->wbuff) - xar->stream.avail_out;
		checksum_update(&(xar->a_sumwrk), xar->wbuff, size);
	}