static int working_tree_entry_cmp(struct working_tree_entry *a,
				  struct working_tree_entry *b, void *keydata)
{
	return strcmp(a->path, b->path);
}