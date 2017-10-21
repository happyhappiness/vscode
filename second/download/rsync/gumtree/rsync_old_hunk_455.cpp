	case r_init:
	    if (!init_done) {
		rx_strm.next_out = NULL;
		rx_strm.zalloc = z_alloc;
		rx_strm.zfree = z_free;
		if (inflateInit2(&rx_strm, -15) != Z_OK) {
		    fprintf(FERROR, "inflate init failed\n");
		    exit_cleanup(1);
		}
		if ((cbuf = malloc(MAX_DATA_COUNT)) == NULL
		    || (dbuf = malloc(CHUNK_SIZE)) == NULL)
		    out_of_memory("recv_deflated_token");
		init_done = 1;
