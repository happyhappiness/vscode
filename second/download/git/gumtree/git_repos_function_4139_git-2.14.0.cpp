struct tree *lookup_tree(const struct object_id *oid)
{
	struct object *obj = lookup_object(oid->hash);
	if (!obj)
		return create_object(oid->hash, alloc_tree_node());
	return object_as_type(obj, OBJ_TREE, 0);
}