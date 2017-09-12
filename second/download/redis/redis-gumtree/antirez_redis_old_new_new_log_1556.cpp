malloc_printf("<jemalloc>: Corrupt redzone %zu byte%s %s %p "
	    "(size %zu), byte=%#x\n", offset, (offset == 1) ? "" : "s",
	    after ? "after" : "before", ptr, usize, byte);