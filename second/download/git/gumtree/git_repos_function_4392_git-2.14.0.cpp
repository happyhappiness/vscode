static inline void init_remotes_hash(void)
{
	if (!remotes_hash.cmpfn)
		hashmap_init(&remotes_hash, (hashmap_cmp_fn)remotes_hash_cmp, NULL, 0);
}