static int base_name_entries_compare(const struct name_entry *a,
				     const struct name_entry *b)
{
	return base_name_compare(a->path, tree_entry_len(a), a->mode,
				 b->path, tree_entry_len(b), b->mode);
}