static void *do_xmalloc(size_t size, int gentle)
{
	void *ret;

	if (memory_limit_check(size, gentle))
		return NULL;
	ret = malloc(size);
	if (!ret && !size)
		ret = malloc(1);
	if (!ret) {
		try_to_free_routine(size);
		ret = malloc(size);
		if (!ret && !size)
			ret = malloc(1);
		if (!ret) {
			if (!gentle)
				die("Out of memory, malloc failed (tried to allocate %lu bytes)",
				    (unsigned long)size);
			else {
				error("Out of memory, malloc failed (tried to allocate %lu bytes)",
				      (unsigned long)size);
				return NULL;
			}
		}
	}
#ifdef XMALLOC_POISON
	memset(ret, 0xA5, size);
#endif
	return ret;
}