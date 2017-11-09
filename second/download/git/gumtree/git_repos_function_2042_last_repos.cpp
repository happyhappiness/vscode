struct object *lookup_unknown_object(const unsigned char *sha1)
{
	struct object *obj = lookup_object(sha1);
	if (!obj)
		obj = create_object(sha1, alloc_object_node());
	return obj;
}