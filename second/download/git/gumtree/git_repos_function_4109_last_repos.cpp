static int cache_entry_cmp(const void *unused_cmp_data,
			   const struct cache_entry *ce1,
			   const struct cache_entry *ce2,
			   const void *remove)
{
	/*
	 * For remove_name_hash, find the exact entry (pointer equality); for
	 * index_file_exists, find all entries with matching hash code and
	 * decide whether the entry matches in same_name.
	 */
	return remove ? !(ce1 == ce2) : 0;
}