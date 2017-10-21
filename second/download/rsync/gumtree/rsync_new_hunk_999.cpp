			if (!init_done) {
				rx_strm.next_out = NULL;
				rx_strm.zalloc = NULL;
				rx_strm.zfree = NULL;
				if (inflateInit2(&rx_strm, -15) != Z_OK) {
					rprintf(FERROR, "inflate init failed\n");
					exit_cleanup(RERR_PROTOCOL);
				}
				if (!(cbuf = new_array(char, MAX_DATA_COUNT))
				    || !(dbuf = new_array(char, AVAIL_OUT_SIZE(CHUNK_SIZE))))
					out_of_memory("recv_deflated_token");
				init_done = 1;
			} else {
