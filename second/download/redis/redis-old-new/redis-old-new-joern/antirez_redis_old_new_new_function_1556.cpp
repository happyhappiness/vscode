static void
arena_redzone_corruption(void *ptr, size_t usize, bool after,
    size_t offset, uint8_t byte)
{

	malloc_printf("<jemalloc>: Corrupt redzone %zu byte%s %s %p "
	    "(size %zu), byte=%#x\n", offset, (offset == 1) ? "" : "s",
	    after ? "after" : "before", ptr, usize, byte);
}