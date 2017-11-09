static inline int compute_dir_lock_nr(
	const struct hashmap *map,
	unsigned int hash)
{
	return hashmap_bucket(map, hash) % LAZY_MAX_MUTEX;
}