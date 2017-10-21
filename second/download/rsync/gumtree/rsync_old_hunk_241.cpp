		/* check previous inflated stuff ended correctly */
		rx_strm.avail_in = 0;
		rx_strm.next_out = dbuf;
		rx_strm.avail_out = CHUNK_SIZE;
		r = inflate(&rx_strm, Z_PACKET_FLUSH);
		n = CHUNK_SIZE - rx_strm.avail_out;
		if (r != Z_OK || n != 0) {
		    fprintf(FERROR, "inflate flush returned %d (%d bytes)\n",
			    r, n);
		    exit_cleanup(1);
		}
		recv_state = r_idle;
	    }
	    if (flag == END_FLAG) {
		/* that's all folks */
		recv_state = r_init;
		return 0;
