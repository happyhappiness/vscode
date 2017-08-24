{
		size_t size;

		r = compression_code(&(a->archive),
		    &(xar->stream), ARCHIVE_Z_FINISH);
		if (r != ARCHIVE_OK && r != ARCHIVE_EOF)
			goto exit_toc;
		size = sizeof(xar->wbuff) - xar->stream.avail_out;
		checksum_update(&(xar->a_sumwrk), xar->wbuff, size);
		if (write_to_temp(a, xar->wbuff, size) != ARCHIVE_OK)
			goto exit_toc;
		if (r == ARCHIVE_EOF)
			break;
		xar->stream.next_out = xar->wbuff;
		xar->stream.avail_out = sizeof(xar->wbuff);
	}