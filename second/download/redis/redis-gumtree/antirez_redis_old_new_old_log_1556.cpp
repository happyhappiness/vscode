malloc_printf("<jemalloc>: Corrupt redzone "
			    "%zu byte%s before %p (size %zu), byte=%#x\n", i,
			    (i == 1) ? "" : "s", ptr, size, byte);