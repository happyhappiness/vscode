 			if (!init_done) {
 				rx_strm.next_out = NULL;
 				rx_strm.zalloc = NULL;
 				rx_strm.zfree = NULL;
 				if (inflateInit2(&rx_strm, -15) != Z_OK) {
 					rprintf(FERROR, "inflate init failed\n");
-					exit_cleanup(1);
+					exit_cleanup(RERR_STREAMIO);
 				}
 				if ((cbuf = malloc(MAX_DATA_COUNT)) == NULL
 				    || (dbuf = malloc(CHUNK_SIZE)) == NULL)
 					out_of_memory("recv_deflated_token");
 				init_done = 1;
 			} else {
