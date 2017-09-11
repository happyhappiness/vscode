		if (munmap(ret, size) == -1) {
			char buf[BUFERROR_BUF];

			buferror(buf, sizeof(buf));
			malloc_printf("<jemalloc: Error in munmap(): %s\n",
			    buf);
			if (opt_abort)
