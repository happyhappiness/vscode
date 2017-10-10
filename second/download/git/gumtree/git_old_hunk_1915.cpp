{
	size_t cur = pack_mapped;
	while (need >= (cur - pack_mapped) && unuse_one_window(NULL))
		; /* nothing */
}

void *xmmap(void *start, size_t length,
	int prot, int flags, int fd, off_t offset)
{
	void *ret = mmap(start, length, prot, flags, fd, offset);
	if (ret == MAP_FAILED) {
		if (!length)
			return NULL;
		release_pack_memory(length);
		ret = mmap(start, length, prot, flags, fd, offset);
		if (ret == MAP_FAILED)
