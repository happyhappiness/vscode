{
	struct cab *cab = (struct cab *)(a->format->data);
	struct cfdata *cfdata;
	const void *d;
	int r, mszip;
	uint16_t uavail;
	char eod = 0;

	cfdata = cab->entry_cfdata;
	/* If the buffer hasn't been allocated, allocate it now. */
	if (cab->uncompressed_buffer == NULL) {
		cab->uncompressed_buffer_size = 0x8000;
		cab->uncompressed_buffer
		    = (unsigned char *)malloc(cab->uncompressed_buffer_size);
		if (cab->uncompressed_buffer == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for CAB reader");
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
	}

	uavail = cfdata->uncompressed_avail;
	if (uavail == cfdata->uncompressed_size) {
		d = cab->uncompressed_buffer + cfdata->read_offset;
		*avail = uavail - cfdata->read_offset;
		return (d);
	}

	if (!cab->entry_cffolder->decompress_init) {
		cab->stream.next_in = NULL;
		cab->stream.avail_in = 0;
		cab->stream.total_in = 0;
		cab->stream.next_out = NULL;
		cab->stream.avail_out = 0;
		cab->stream.total_out = 0;
		if (cab->stream_valid)
			r = inflateReset(&cab->stream);
		else
			r = inflateInit2(&cab->stream,
			    -15 /* Don't check for zlib header */);
		if (r != Z_OK) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Can't initialize deflate decompression.");
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
		/* Stream structure has been set up. */
		cab->stream_valid = 1;
		/* We've initialized decompression for this stream. */
		cab->entry_cffolder->decompress_init = 1;
	}

	if (cfdata->compressed_bytes_remaining == cfdata->compressed_size)
		mszip = 2;
	else
		mszip = 0;
	eod = 0;
	cab->stream.total_out = uavail;
	/*
	 * We always uncompress all data in current CFDATA.
	 */
	while (!eod && cab->stream.total_out < cfdata->uncompressed_size) {
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
	uavail = (uint16_t)cab->stream.total_out;

	if (uavail < cfdata->uncompressed_size) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid uncompressed size (%d < %d)",
		    uavail, cfdata->uncompressed_size);
		*avail = ARCHIVE_FATAL;
		return (NULL);
	}

	/*
	 * Note: I suspect there is a bug in makecab.exe because, in rare
	 * case, compressed bytes are still remaining regardless we have
	 * gotten all uncompressed bytes, which size is recorded in CFDATA,
	 * as much as we need, and we have to use the garbage so as to
	 * correctly compute the sum of CFDATA accordingly.
	 */
	if (cfdata->compressed_bytes_remaining > 0) {
		ssize_t bytes_avail;

		d = __archive_read_ahead(a, cfdata->compressed_bytes_remaining,
		    &bytes_avail);
		if (bytes_avail <= 0) {
			*avail = truncated_error(a);
			return (NULL);
		}
		cfdata->unconsumed = cfdata->compressed_bytes_remaining;
		cfdata->sum_ptr = d;
		if (cab_minimum_consume_cfdata(a, cfdata->unconsumed) < 0) {
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
	}

	/*
	 * Set dictionary data for decompressing of next CFDATA, which
	 * in the same folder. This is why we always do decompress CFDATA
	 * even if beginning CFDATA or some of CFDATA are not used in
	 * skipping file data.
	 */
	if (cab->entry_cffolder->cfdata_index <
	    cab->entry_cffolder->cfdata_count) {
		r = inflateReset(&cab->stream);
		if (r != Z_OK)
			goto zlibfailed;
		r = inflateSetDictionary(&cab->stream,
		    cab->uncompressed_buffer, cfdata->uncompressed_size);
		if (r != Z_OK)
			goto zlibfailed;
	}

	d = cab->uncompressed_buffer + cfdata->read_offset;
	*avail = uavail - cfdata->read_offset;
	cfdata->uncompressed_avail = uavail;

	return (d);

zlibfailed:
	switch (r) {
	case Z_MEM_ERROR:
		archive_set_error(&a->archive, ENOMEM,
		    "Out of memory for deflate decompression");
		break;
	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Deflate decompression failed (%d)", r);
		break;
	}
	*avail = ARCHIVE_FATAL;
	return (NULL);
nomszip:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
	    "CFDATA incorrect(no MSZIP signature)");
	*avail = ARCHIVE_FATAL;
	return (NULL);
}