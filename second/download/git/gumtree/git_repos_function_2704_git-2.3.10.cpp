struct cache_tree *cache_tree_read(const char *buffer, unsigned long size)
{
	if (buffer[0])
		return NULL; /* not the whole tree */
	return read_one(&buffer, &size);
}