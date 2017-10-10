
unmap:
	munmap(mmap, mmap_size);
	die("index file corrupt");
}

int read_index_from(struct index_state *istate, const char *path)
{
	struct split_index *split_index;
	int ret;

	/* istate->initialized covers both .git/index and .git/sharedindex.xxx */
	if (istate->initialized)
		return istate->cache_nr;

	ret = do_read_index(istate, path, 0);
