static const unsigned char *replace_sha1_access(size_t index, void *table)
{
	struct replace_object **replace = table;
	return replace[index]->original;
}