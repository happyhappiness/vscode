			if (deflateInit2(&tx_strm, compression_level,
					 Z_DEFLATED, -15, 8,
					 Z_DEFAULT_STRATEGY) != Z_OK) {
				rprintf(FERROR, "compression init failed\n");
				exit_cleanup(RERR_STREAMIO);
			}
			if ((obuf = new_array(char, MAX_DATA_COUNT+2)) == NULL)
				out_of_memory("send_deflated_token");
			init_done = 1;
		} else
			deflateReset(&tx_strm);
		last_run_end = 0;
		run_start = token;
