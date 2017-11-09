static int pair_cmp(const void *unused_cmp_data,
		    struct pair_entry *a, struct pair_entry *b,
		    void *unused_keydata)
{
	return strcmp(a->path, b->path);
}