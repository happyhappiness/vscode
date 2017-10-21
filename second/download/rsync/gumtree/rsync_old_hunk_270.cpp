	} while (nb != 0 || tx_strm.avail_out == 0);
    }

    if (token != -1) {
	/* add the data in the current block to the compressor's
	   history and hash table */
	tx_strm.next_in = map_ptr(buf, offset, toklen);
	tx_strm.avail_in = toklen;
	tx_strm.next_out = NULL;
	tx_strm.avail_out = 2 * toklen;
	r = deflate(&tx_strm, Z_INSERT_ONLY);
	if (r != Z_OK || tx_strm.avail_in != 0) {
	    fprintf(FERROR, "deflate on token returned %d (%d bytes left)\n",
