	/* initialization */
	if (!init_done) {
	    tx_strm.next_in = NULL;
	    tx_strm.zalloc = z_alloc;
	    tx_strm.zfree = z_free;
	    if (deflateInit2(&tx_strm, Z_DEFAULT_COMPRESSION, 8,
			     -15, 8, Z_DEFAULT_STRATEGY, -4) != Z_OK) {
		fprintf(FERROR, "compression init failed\n");
		exit_cleanup(1);
	    }
	    if ((obuf = malloc(MAX_DATA_COUNT+2)) == NULL)
		out_of_memory("send_deflated_token");
	    init_done = 1;
