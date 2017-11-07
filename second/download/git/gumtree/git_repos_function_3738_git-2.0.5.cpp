static inline struct commit_name *find_commit_name(const unsigned char *peeled)
{
	struct commit_name key;
	hashmap_entry_init(&key, hash_sha1(peeled));
	return hashmap_get(&names, &key, peeled);
}