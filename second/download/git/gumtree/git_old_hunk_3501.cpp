	}
	if (verbose && !was_same)
		printf("add '%s'\n", path);
	return 0;
}

int add_file_to_index(struct index_state *istate, const char *path, int flags)
{
	struct stat st;
	if (lstat(path, &st))
		die_errno("unable to stat '%s'", path);
	return add_to_index(istate, path, &st, flags);
}

struct cache_entry *make_cache_entry(unsigned int mode,
		const unsigned char *sha1, const char *path, int stage,
		unsigned int refresh_options)
{
