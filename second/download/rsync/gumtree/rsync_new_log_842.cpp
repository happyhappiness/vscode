fprintf(stderr, "need to write %ld bytes, iobuf.out.buf is only %ld bytes.\n",
				(long)needed, (long)(iobuf.out.size - iobuf.out_empty_len));