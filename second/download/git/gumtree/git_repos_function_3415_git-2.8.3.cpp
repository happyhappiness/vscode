static struct dir_entry *find_dir_entry(struct index_state *istate,
		const char *name, unsigned int namelen)
{
	struct dir_entry key;
	hashmap_entry_init(&key, memihash(name, namelen));
	key.namelen = namelen;
	return hashmap_get(&istate->dir_hash, &key, name);
}