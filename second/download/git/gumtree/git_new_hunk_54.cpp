}

struct tree *lookup_tree(const unsigned char *sha1)
{
	struct object *obj = lookup_object(sha1);
	if (!obj)
		return create_object(sha1, alloc_tree_node());
	return object_as_type(obj, OBJ_TREE, 0);
}

int parse_tree_buffer(struct tree *item, void *buffer, unsigned long size)
{
	if (item->object.parsed)
		return 0;
