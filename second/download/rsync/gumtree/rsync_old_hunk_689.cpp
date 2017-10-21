				rx_strm.zfree = NULL;
				if (inflateInit2(&rx_strm, -15) != Z_OK) {
					rprintf(FERROR, "inflate init failed\n");
					exit_cleanup(RERR_STREAMIO);
				}
				if (!(cbuf = new_array(char, MAX_DATA_COUNT))
				    || !(dbuf = new_array(char, CHUNK_SIZE)))
					out_of_memory("recv_deflated_token");
				init_done = 1;
			} else {
				inflateReset(&rx_strm);
			}
			recv_state = r_idle;
