static void mark_object_for_connectivity(const struct object_id *oid)
{
	struct object *obj = lookup_unknown_object(oid->hash);
	obj->flags |= HAS_OBJ;
}