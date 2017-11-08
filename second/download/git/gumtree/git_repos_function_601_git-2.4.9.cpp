struct commit *lookup_commit(const unsigned char *sha1)
{
	struct object *obj = lookup_object(sha1);
	if (!obj)
		return create_object(sha1, alloc_commit_node());
	return object_as_type(obj, OBJ_COMMIT, 0);
}