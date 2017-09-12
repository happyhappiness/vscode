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