	tx_strm.avail_in = 0;
	tx_strm.avail_out = 0;
	do {
	    if (tx_strm.avail_in == 0 && nb != 0) {
		/* give it some more input */
		n = MIN(nb, CHUNK_SIZE);
		tx_strm.next_in = map_ptr(buf, offset, n);
		tx_strm.avail_in = n;
		nb -= n;
		offset += n;
	    }
	    if (tx_strm.avail_out == 0) {
		tx_strm.next_out = obuf + 2;
		tx_strm.avail_out = MAX_DATA_COUNT;
	    }
	    r = deflate(&tx_strm, nb? Z_NO_FLUSH: Z_PACKET_FLUSH);
	    if (r != Z_OK) {
		fprintf(FERROR, "deflate returned %d\n", r);
		exit_cleanup(1);
