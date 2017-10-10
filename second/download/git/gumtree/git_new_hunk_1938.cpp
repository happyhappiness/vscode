		if (!ret)
			die("Out of memory, strdup failed");
	}
	return ret;
}

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

void *xmalloc(size_t size)
{
	return do_xmalloc(size, 0);
}

static void *do_xmallocz(size_t size, int gentle)
{
	void *ret;
	if (unsigned_add_overflows(size, 1)) {
		if (gentle) {
			error("Data too large to fit into virtual memory space.");
			return NULL;
		} else
			die("Data too large to fit into virtual memory space.");
	}
	ret = do_xmalloc(size + 1, gentle);
	if (ret)
		((char*)ret)[size] = 0;
	return ret;
}

void *xmallocz(size_t size)
{
	return do_xmallocz(size, 0);
}

void *xmallocz_gently(size_t size)
{
	return do_xmallocz(size, 1);
}

/*
 * xmemdupz() allocates (len + 1) bytes of memory, duplicates "len" bytes of
 * "data" to the allocated memory, zero terminates the allocated memory,
 * and returns a pointer to the allocated memory. If the allocation fails,
 * the program dies.
 */
