void *xmallocz(size_t size)
{
	void *ret;
	if (unsigned_add_overflows(size, 1))
		die("Data too large to fit into virtual memory space.");
	ret = xmalloc(size + 1);
	((char*)ret)[size] = 0;
	return ret;
}