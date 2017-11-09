int write_cache_as_tree(unsigned char *sha1, int flags, const char *prefix)
{
	return write_index_as_tree(sha1, &the_index, get_index_file(), flags, prefix);
}