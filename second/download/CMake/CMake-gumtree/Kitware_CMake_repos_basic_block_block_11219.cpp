{
		ssize_t bytes_avail;

		cab->xstrm.next_out =
		    cab->uncompressed_buffer + cab->xstrm.total_out;
		cab->xstrm.avail_out =
		    cfdata->uncompressed_size - cab->xstrm.total_out;

		d = __archive_read_ahead(a, 1, &bytes_avail);
		if (bytes_avail <= 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated CAB file data");
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
		if (bytes_avail > cfdata->compressed_bytes_remaining)
			bytes_avail = cfdata->compressed_bytes_remaining;

		cab->xstrm.next_in = d;
		cab->xstrm.avail_in = bytes_avail;
		cab->xstrm.total_in = 0;
		r = lzx_decode(&cab->xstrm,
		    cfdata->compressed_bytes_remaining == bytes_avail);
		switch (r) {
		case ARCHIVE_OK:
		case ARCHIVE_EOF:
			break;
		default:
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "LZX decompression failed (%d)", r);
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
		cfdata->unconsumed = cab->xstrm.total_in;
		cfdata->sum_ptr = d;
		if (cab_minimum_consume_cfdata(a, cfdata->unconsumed) < 0) {
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
	}