static struct remote *make_remote(const char *name, int len)
{
	struct remote *ret, *replaced;
	struct remotes_hash_key lookup;
	struct hashmap_entry lookup_entry;

	if (!len)
		len = strlen(name);

	init_remotes_hash();
	lookup.str = name;
	lookup.len = len;
	hashmap_entry_init(&lookup_entry, memhash(name, len));

	if ((ret = hashmap_get(&remotes_hash, &lookup_entry, &lookup)) != NULL)
		return ret;

	ret = xcalloc(1, sizeof(struct remote));
	ret->prune = -1;  /* unspecified */
	ALLOC_GROW(remotes, remotes_nr + 1, remotes_alloc);
	remotes[remotes_nr++] = ret;
	ret->name = xstrndup(name, len);

	hashmap_entry_init(ret, lookup_entry.hash);
	replaced = hashmap_put(&remotes_hash, ret);
	assert(replaced == NULL);  /* no previous entry overwritten */
	return ret;
}