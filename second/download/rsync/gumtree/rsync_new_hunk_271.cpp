		saved_flag = 0;
	    } else
		flag = read_byte(f);
	    if ((flag & 0xC0) == DEFLATED_DATA) {
		n = ((flag & 0x3f) << 8) + read_byte(f);
		read_buf(f, cbuf, n);
		rx_strm.next_in = (Bytef *)cbuf;
		rx_strm.avail_in = n;
		recv_state = r_inflating;
		break;
	    }
	    if (recv_state == r_inflated) {
		/* check previous inflated stuff ended correctly */
		rx_strm.avail_in = 0;
		rx_strm.next_out = (Bytef *)dbuf;
		rx_strm.avail_out = CHUNK_SIZE;
		r = inflate(&rx_strm, Z_PACKET_FLUSH);
		n = CHUNK_SIZE - rx_strm.avail_out;
		if (r != Z_OK) {
		    fprintf(FERROR, "inflate flush returned %d (%d bytes)\n",
			    r, n);
