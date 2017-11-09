static inline int tree_entry_len(const struct name_entry *ne)
{
	return (const char *)ne->oid - ne->path - 1;
}