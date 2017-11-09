static int invalidate_one_component(struct untracked_cache *uc,
				    struct untracked_cache_dir *dir,
				    const char *path, int len)
{
	const char *rest = strchr(path, '/');

	if (rest) {
		int component_len = rest - path;
		struct untracked_cache_dir *d =
			lookup_untracked(uc, dir, path, component_len);
		int ret =
			invalidate_one_component(uc, d, rest + 1,
						 len - (component_len + 1));
		if (ret)
			invalidate_one_directory(uc, dir);
		return ret;
	}

	invalidate_one_directory(uc, dir);
	return uc->dir_flags & DIR_SHOW_OTHER_DIRECTORIES;
}