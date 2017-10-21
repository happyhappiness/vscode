 		rx_strm.avail_in = 0;
 		rx_strm.next_out = (Bytef *)dbuf;
 		rx_strm.avail_out = CHUNK_SIZE;
 		r = inflate(&rx_strm, Z_PACKET_FLUSH);
 		n = CHUNK_SIZE - rx_strm.avail_out;
 		if (r != Z_OK) {
-		    fprintf(FERROR, "inflate flush returned %d (%d bytes)\n",
+		    rprintf(FERROR, "inflate flush returned %d (%d bytes)\n",
 			    r, n);
 		    exit_cleanup(1);
 		}
 		if (n != 0) {
 		    /* have to return some more data and
 		       save the flag for later. */
