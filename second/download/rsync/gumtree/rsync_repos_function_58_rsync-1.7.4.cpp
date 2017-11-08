static void
send_deflated_token(int f, int token,
		    struct map_struct *buf, int offset, int nb, int toklen)
{
    int n, r;
    static int init_done;

    if (last_token == -1) {
	/* initialization */
	if (!init_done) {
	    tx_strm.next_in = NULL;
	    tx_strm.zalloc = z_alloc;
	    tx_strm.zfree = z_free;
	    if (deflateInit2(&tx_strm, Z_DEFAULT_COMPRESSION, 8,
			     -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
		fprintf(FERROR, "compression init failed\n");
		exit_cleanup(1);
	    }
	    if ((obuf = malloc(MAX_DATA_COUNT+2)) == NULL)
		out_of_memory("send_deflated_token");
	    init_done = 1;
	} else
	    deflateReset(&tx_strm);
	run_start = token;
	last_run_end = 0;

    } else if (nb != 0 || token != last_token + 1
	       || token >= run_start + 65536) {
	/* output previous run */
	r = run_start - last_run_end;
	n = last_token - run_start;
	if (r >= 0 && r <= 63) {
	    write_byte(f, (n==0? TOKEN_REL: TOKENRUN_REL) + r);
	} else {
	    write_byte(f, (n==0? TOKEN_LONG: TOKENRUN_LONG));
	    write_int(f, run_start);
	}
	if (n != 0) {
	    write_byte(f, n);
	    write_byte(f, n >> 8);
	}
	last_run_end = last_token;
	run_start = token;
    }

    last_token = token;

    if (nb != 0) {
	/* deflate the data starting at offset */
	tx_strm.avail_in = 0;
	tx_strm.avail_out = 0;
	do {
	    if (tx_strm.avail_in == 0 && nb != 0) {
		/* give it some more input */
		n = MIN(nb, CHUNK_SIZE);
		tx_strm.next_in = (Bytef *)map_ptr(buf, offset, n);
		tx_strm.avail_in = n;
		nb -= n;
		offset += n;
	    }
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
		    obuf[1] = n;
		    write_buf(f, obuf, n+2);
		}
	    }
	} while (nb != 0 || tx_strm.avail_out == 0);
    }

    if (token != -1) {
	/* add the data in the current block to the compressor's
	   history and hash table */
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
	write_byte(f, END_FLAG);
    }
}