static void *xmalloc(size_t size)
{
	void *ret = malloc(size);
	if (!ret && !size)
		ret = malloc(1);
	if (!ret)
		 die("Out of memory");
	return ret;
}