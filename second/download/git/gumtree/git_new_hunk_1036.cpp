
unmap:
	munmap(mmap, mmap_size);
	die("index file corrupt");
}

/*
 * Signal that the shared index is used by updating its mtime.
 *
 * This way, shared index can be removed if they have not been used
 * for some time.
 */
static void freshen_shared_index(char *base_sha1_hex, int warn)
{
	char *shared_index = git_pathdup("sharedindex.%s", base_sha1_hex);
	if (!check_and_freshen_file(shared_index, 1) && warn)
		warning("could not freshen shared index '%s'", shared_index);
	free(shared_index);
}

int read_index_from(struct index_state *istate, const char *path)
{
	struct split_index *split_index;
	int ret;
	char *base_sha1_hex;
	const char *base_path;

	/* istate->initialized covers both .git/index and .git/sharedindex.xxx */
	if (istate->initialized)
		return istate->cache_nr;

	ret = do_read_index(istate, path, 0);
