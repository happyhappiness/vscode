struct commit *lookup_commit(const struct object_id *oid)
{
	struct object *obj = lookup_object(oid->hash);
	if (!obj)
		return create_object(oid->hash, alloc_commit_node());
	return object_as_type(obj, OBJ_COMMIT, 0);
}