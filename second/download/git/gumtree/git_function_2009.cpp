void *xmmap(void *start, size_t length,
	int prot, int flags, int fd, off_t offset)
{
	void *ret = xmmap_gently(start, length, prot, flags, fd, offset);
	if (ret == MAP_FAILED)
		die_errno("mmap failed");
	return ret;
}