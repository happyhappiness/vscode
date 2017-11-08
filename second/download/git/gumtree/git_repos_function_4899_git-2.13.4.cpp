static inline struct commit_name *find_commit_name(const struct object_id *peeled)
{
	return hashmap_get_from_hash(&names, sha1hash(peeled->hash), peeled->hash);
}