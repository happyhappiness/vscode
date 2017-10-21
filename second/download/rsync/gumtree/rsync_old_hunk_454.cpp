	tx_strm.next_in = (Bytef *)map_ptr(buf, offset, toklen);
	tx_strm.avail_in = toklen;
	tx_strm.next_out = NULL;
	tx_strm.avail_out = 2 * toklen;
	r = deflate(&tx_strm, Z_INSERT_ONLY);
	if (r != Z_OK || tx_strm.avail_in != 0) {
	    fprintf(FERROR, "deflate on token returned %d (%d bytes left)\n",
		    r, tx_strm.avail_in);
	    exit_cleanup(1);
	}

    } else {
	/* end of file - clean up */
