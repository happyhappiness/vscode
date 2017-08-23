static const void *
cab_read_ahead_cfdata_lzx(struct archive_read *a, ssize_t *avail)
{
	struct cab *cab = (struct cab *)(a->format->data);
	struct cfdata *cfdata;
	const void *d;
	int r;
	uint16_t uavail;

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
		r = lzx_decode_init(&cab->xstrm,
		    cab->entry_cffolder->compdata);
		if (r != ARCHIVE_OK) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Can't initialize LZX decompression.");
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
		/* We've initialized decompression for this stream. */
		cab->entry_cffolder->decompress_init = 1;
	}

	/* Clean up remaining bits of previous CFDATA. */
	lzx_cleanup_bitstream(&cab->xstrm);
	cab->xstrm.total_out = uavail;
	while (cab->xstrm.total_out < cfdata->uncompressed_size) {
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

	uavail = (uint16_t)cab->xstrm.total_out;
	/*
	 * Make sure a read pointer advances to next CFDATA.
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
	 * Translation reversal of x86 processor CALL byte sequence(E8).
	 */
	lzx_translation(&cab->xstrm, cab->uncompressed_buffer,
	    cfdata->uncompressed_size,
	    (cab->entry_cffolder->cfdata_index-1) * 0x8000);

	d = cab->uncompressed_buffer + cfdata->read_offset;
	*avail = uavail - cfdata->read_offset;
	cfdata->uncompressed_avail = uavail;

	return (d);
}