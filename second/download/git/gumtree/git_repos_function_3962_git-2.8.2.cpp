static inline int tree_entry_len(const struct name_entry *ne)
{
	return (const char *)ne->sha1 - ne->path - 1;
}