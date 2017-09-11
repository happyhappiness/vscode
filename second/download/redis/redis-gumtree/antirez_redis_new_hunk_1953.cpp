	}
}

#ifdef JEMALLOC_JET
#undef arena_redzone_corruption
#define	arena_redzone_corruption JEMALLOC_N(arena_redzone_corruption_impl)
#endif
static void
arena_redzone_corruption(void *ptr, size_t usize, bool after,
    size_t offset, uint8_t byte)
{

	malloc_printf("<jemalloc>: Corrupt redzone %zu byte%s %s %p "
	    "(size %zu), byte=%#x\n", offset, (offset == 1) ? "" : "s",
	    after ? "after" : "before", ptr, usize, byte);
}
#ifdef JEMALLOC_JET
#undef arena_redzone_corruption
#define	arena_redzone_corruption JEMALLOC_N(arena_redzone_corruption)
arena_redzone_corruption_t *arena_redzone_corruption =
    JEMALLOC_N(arena_redzone_corruption_impl);
#endif

static void
arena_redzones_validate(void *ptr, arena_bin_info_t *bin_info, bool reset)
{
	size_t size = bin_info->reg_size;
	size_t redzone_size = bin_info->redzone_size;
	size_t i;
	bool error = false;

	for (i = 1; i <= redzone_size; i++) {
		uint8_t *byte = (uint8_t *)((uintptr_t)ptr - i);
		if (*byte != 0xa5) {
			error = true;
			arena_redzone_corruption(ptr, size, false, i, *byte);
			if (reset)
				*byte = 0xa5;
		}
	}
	for (i = 0; i < redzone_size; i++) {
		uint8_t *byte = (uint8_t *)((uintptr_t)ptr + size + i);
		if (*byte != 0xa5) {
			error = true;
			arena_redzone_corruption(ptr, size, true, i, *byte);
			if (reset)
				*byte = 0xa5;
		}
	}
	if (opt_abort && error)
		abort();
}

#ifdef JEMALLOC_JET
#undef arena_dalloc_junk_small
#define	arena_dalloc_junk_small JEMALLOC_N(arena_dalloc_junk_small_impl)
#endif
void
arena_dalloc_junk_small(void *ptr, arena_bin_info_t *bin_info)
{
	size_t redzone_size = bin_info->redzone_size;

	arena_redzones_validate(ptr, bin_info, false);
	memset((void *)((uintptr_t)ptr - redzone_size), 0x5a,
	    bin_info->reg_interval);
}
#ifdef JEMALLOC_JET
#undef arena_dalloc_junk_small
#define	arena_dalloc_junk_small JEMALLOC_N(arena_dalloc_junk_small)
arena_dalloc_junk_small_t *arena_dalloc_junk_small =
    JEMALLOC_N(arena_dalloc_junk_small_impl);
#endif

void
arena_quarantine_junk_small(void *ptr, size_t usize)
{
	size_t binind;
	arena_bin_info_t *bin_info;
	cassert(config_fill);
	assert(opt_junk);
	assert(opt_quarantine);
	assert(usize <= SMALL_MAXCLASS);

	binind = SMALL_SIZE2BIN(usize);
	bin_info = &arena_bin_info[binind];
	arena_redzones_validate(ptr, bin_info, true);
}

void *
arena_malloc_small(arena_t *arena, size_t size, bool zero)
