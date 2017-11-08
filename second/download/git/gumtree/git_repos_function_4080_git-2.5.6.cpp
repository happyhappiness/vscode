static inline struct commit_name *find_commit_name(const unsigned char *peeled)
{
	return hashmap_get_from_hash(&names, sha1hash(peeled), peeled);
}