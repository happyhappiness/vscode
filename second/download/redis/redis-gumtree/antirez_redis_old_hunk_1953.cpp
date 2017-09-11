	}
}

void
arena_dalloc_junk_small(void *ptr, arena_bin_info_t *bin_info)
{
	size_t size = bin_info->reg_size;
	size_t redzone_size = bin_info->redzone_size;
	size_t i;
	bool error = false;

	for (i = 1; i <= redzone_size; i++) {
		unsigned byte;
		if ((byte = *(uint8_t *)((uintptr_t)ptr - i)) != 0xa5) {
			error = true;
			malloc_printf("<jemalloc>: Corrupt redzone "
			    "%zu byte%s before %p (size %zu), byte=%#x\n", i,
			    (i == 1) ? "" : "s", ptr, size, byte);
		}
	}
	for (i = 0; i < redzone_size; i++) {
		unsigned byte;
		if ((byte = *(uint8_t *)((uintptr_t)ptr + size + i)) != 0xa5) {
			error = true;
			malloc_printf("<jemalloc>: Corrupt redzone "
			    "%zu byte%s after end of %p (size %zu), byte=%#x\n",
			    i, (i == 1) ? "" : "s", ptr, size, byte);
		}
	}
	if (opt_abort && error)
		abort();

	memset((void *)((uintptr_t)ptr - redzone_size), 0x5a,
	    bin_info->reg_interval);
}

void *
arena_malloc_small(arena_t *arena, size_t size, bool zero)
