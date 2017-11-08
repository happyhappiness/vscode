static int pair_cmp(struct pair_entry *a, struct pair_entry *b, void *keydata)
{
	return strcmp(a->path, b->path);
}