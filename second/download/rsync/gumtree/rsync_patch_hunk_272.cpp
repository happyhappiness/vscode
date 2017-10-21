 		rx_run += read_byte(f) << 8;
 		recv_state = r_running;
 	    }
 	    return -1 - rx_token;
 
 	case r_inflating:
-	    rx_strm.next_out = dbuf;
+	    rx_strm.next_out = (Bytef *)dbuf;
 	    rx_strm.avail_out = CHUNK_SIZE;
 	    r = inflate(&rx_strm, Z_NO_FLUSH);
 	    n = CHUNK_SIZE - rx_strm.avail_out;
 	    if (r != Z_OK) {
 		fprintf(FERROR, "inflate returned %d (%d bytes)\n", r, n);
 		exit_cleanup(1);
