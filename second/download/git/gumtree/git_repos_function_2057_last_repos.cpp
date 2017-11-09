static inline int ce_path_match(const struct cache_entry *ce,
				const struct pathspec *pathspec,
				char *seen)
{
	return match_pathspec(pathspec, ce->name, ce_namelen(ce), 0, seen,
			      S_ISDIR(ce->ce_mode) || S_ISGITLINK(ce->ce_mode));
}