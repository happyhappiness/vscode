{
	size_t cur = pack_mapped;
	while (need >= (cur - pack_mapped) && unuse_one_window(NULL))
		; /* nothing */
}

static void mmap_limit_check(size_t length)
{
	static size_t limit = 0;
	if (!limit) {
		limit = git_env_ulong("GIT_MMAP_LIMIT", 0);
		if (!limit)
			limit = SIZE_MAX;
	}
	if (length > limit)
		die("attempting to mmap %"PRIuMAX" over limit %"PRIuMAX,
		    (uintmax_t)length, (uintmax_t)limit);
}

void *xmmap(void *start, size_t length,
	int prot, int flags, int fd, off_t offset)
{
	void *ret;

	mmap_limit_check(length);
	ret = mmap(start, length, prot, flags, fd, offset);
	if (ret == MAP_FAILED) {
		if (!length)
			return NULL;
		release_pack_memory(length);
		ret = mmap(start, length, prot, flags, fd, offset);
		if (ret == MAP_FAILED)
