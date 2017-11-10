struct blob *lookup_blob(const unsigned char *sha1)
{
	struct object *obj = lookup_object(sha1);
	if (!obj)
		return create_object(sha1, alloc_blob_node());
	return object_as_type(obj, OBJ_BLOB, 0);
}