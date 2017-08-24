{
		ssize_t bytes_avail;

		cab->stream.next_out =
		    cab->uncompressed_buffer + cab->stream.total_out;
		cab->stream.avail_out =
		    cfdata->uncompressed_size - cab->stream.total_out;

		d = __archive_read_ahead(a, 1, &bytes_avail);
		if (bytes_avail <= 0) {
			*avail = truncated_error(a);
			return (NULL);
		}
		if (bytes_avail > cfdata->compressed_bytes_remaining)
			bytes_avail = cfdata->compressed_bytes_remaining;
		/*
		 * A bug in zlib.h: stream.next_in should be marked 'const'
		 * but isn't (the library never alters data through the
		 * next_in pointer, only reads it).  The result: this ugly
		 * cast to remove 'const'.
		 */
		cab->stream.next_in = (Bytef *)(uintptr_t)d;
		cab->stream.avail_in = (uInt)bytes_avail;
		cab->stream.total_in = 0;

		/* Cut out a tow-byte MSZIP signature(0x43, 0x4b). */
		if (mszip > 0) {
			if (bytes_avail <= 0)
				goto nomszip;
			if (bytes_avail <= mszip) {
				if (mszip == 2) {
					if (cab->stream.next_in[0] != 0x43)
						goto nomszip;
					if (bytes_avail > 1 &&
					    cab->stream.next_in[1] != 0x4b)
						goto nomszip;
				} else if (cab->stream.next_in[0] != 0x4b)
					goto nomszip;
				cfdata->unconsumed = bytes_avail;
				cfdata->sum_ptr = d;
				if (cab_minimum_consume_cfdata(
				    a, cfdata->unconsumed) < 0) {
					*avail = ARCHIVE_FATAL;
					return (NULL);
				}
				mszip -= (int)bytes_avail;
				continue;
			}
			if (mszip == 1 && cab->stream.next_in[0] != 0x4b)
				goto nomszip;
			else if (cab->stream.next_in[0] != 0x43 ||
			    cab->stream.next_in[1] != 0x4b)
				goto nomszip;
			cab->stream.next_in += mszip;
			cab->stream.avail_in -= mszip;
			cab->stream.total_in += mszip;
			mszip = 0;
		}

		r = inflate(&cab->stream, 0);
		switch (r) {
		case Z_OK:
			break;
		case Z_STREAM_END:
			eod = 1;
			break;
		default:
			goto zlibfailed;
		}
		cfdata->unconsumed = cab->stream.total_in;
		cfdata->sum_ptr = d;
		if (cab_minimum_consume_cfdata(a, cfdata->unconsumed) < 0) {
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
	}