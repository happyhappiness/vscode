
		remaining = tag & 0xFFFFFF;
		tag = (tag >> 24) - MPLEX_BASE;

		switch (tag) {
		case MSG_DATA:
			if (!buffer || remaining > bufferSz) {
				buffer = realloc_array(buffer, char, remaining);
				if (!buffer) out_of_memory("read_unbuffered");
				bufferSz = remaining;
			}
			read_loop(fd, buffer, remaining);
			bufferIdx = 0;
			break;
		case MSG_INFO:
		case MSG_ERROR:
			if (remaining >= sizeof line) {
				rprintf(FERROR, "multiplexing overflow %d:%ld\n\n",
					tag, (long)remaining);
