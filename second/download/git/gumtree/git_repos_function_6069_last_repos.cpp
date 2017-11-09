static int working_tree_entry_cmp(const void *unused_cmp_data,
				  struct working_tree_entry *a,
				  struct working_tree_entry *b,
				  void *unused_keydata)
{
	return strcmp(a->path, b->path);
}