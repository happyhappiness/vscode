static struct dir_entry *find_dir_entry__hash(struct index_state *istate,
		const char *name, unsigned int namelen, unsigned int hash)
{
	struct dir_entry key;
	hashmap_entry_init(&key, hash);
	key.namelen = namelen;
	return hashmap_get(&istate->dir_hash, &key, name);
}