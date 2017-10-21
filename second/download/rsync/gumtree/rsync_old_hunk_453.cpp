	    if (tx_strm.avail_out == 0) {
		tx_strm.next_out = (Bytef *)(obuf + 2);
		tx_strm.avail_out = MAX_DATA_COUNT;
	    }
	    r = deflate(&tx_strm, nb? Z_NO_FLUSH: Z_PACKET_FLUSH);
	    if (r != Z_OK) {
		fprintf(FERROR, "deflate returned %d\n", r);
		exit_cleanup(1);
	    }
	    if (nb == 0 || tx_strm.avail_out == 0) {
		n = MAX_DATA_COUNT - tx_strm.avail_out;
		if (n > 0) {
		    obuf[0] = DEFLATED_DATA + (n >> 8);
