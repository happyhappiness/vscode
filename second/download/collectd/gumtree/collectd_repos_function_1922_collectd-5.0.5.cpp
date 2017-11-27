static TC_HANDLE_T
alloc_handle(const char *tablename, unsigned int size, unsigned int num_rules)
{
	TC_HANDLE_T h;


	h = malloc(sizeof(STRUCT_TC_HANDLE));
	if (!h) {
		errno = ENOMEM;
		return NULL;
	}
	memset(h, 0, sizeof(*h));
	INIT_LIST_HEAD(&h->chains);
	strcpy(h->info.name, tablename);

	h->entries = malloc(sizeof(STRUCT_GET_ENTRIES) + size);
	if (!h->entries)
		goto out_free_handle;

	strcpy(h->entries->name, tablename);
	h->entries->size = size;

	return h;

out_free_handle:
	free(h);

	return NULL;
}