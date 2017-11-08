static inline int traverse_path_len(const struct traverse_info *info, const struct name_entry *n)
{
	return info->pathlen + tree_entry_len(n);
}