int get_sha1_tree(const char *name, unsigned char *sha1)
{
	struct object_context unused;
	return get_sha1_with_context(name, GET_SHA1_TREE,
				     sha1, &unused);
}