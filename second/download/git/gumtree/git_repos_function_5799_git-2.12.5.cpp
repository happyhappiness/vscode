static int path_entry_cmp(struct path_entry *a, struct path_entry *b, void *key)
{
	return strcmp(a->path, key ? key : b->path);
}