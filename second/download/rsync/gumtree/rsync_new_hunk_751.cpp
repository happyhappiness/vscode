
		remaining = tag & 0xFFFFFF;
		tag = (tag >> 24) - MPLEX_BASE;

		switch (tag) {
		case MSG_DATA:
			if (remaining > iobuf_in_siz) {
				if (!(iobuf_in = realloc_array(iobuf_in, char,
							       remaining)))
					out_of_memory("readfd_unbuffered");
				iobuf_in_siz = remaining;
			}
			read_loop(fd, iobuf_in, remaining);
			iobuf_in_ndx = 0;
			break;
		case MSG_INFO:
		case MSG_ERROR:
			if (remaining >= sizeof line) {
				rprintf(FERROR, "multiplexing overflow %d:%ld\n\n",
					tag, (long)remaining);
