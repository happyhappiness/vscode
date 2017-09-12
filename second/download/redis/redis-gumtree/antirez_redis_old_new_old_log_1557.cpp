malloc_printf("<jemalloc>: Corrupt redzone "
			    "%zu byte%s after end of %p (size %zu), byte=%#x\n",
			    i, (i == 1) ? "" : "s", ptr, size, byte);