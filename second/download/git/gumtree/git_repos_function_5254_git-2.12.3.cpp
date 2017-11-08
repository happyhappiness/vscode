static void mark_object_for_connectivity(const unsigned char *sha1)
{
	struct object *obj = lookup_unknown_object(sha1);
	obj->flags |= HAS_OBJ;
}