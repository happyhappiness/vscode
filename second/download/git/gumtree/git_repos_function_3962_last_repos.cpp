static void one_remote_object(const struct object_id *oid)
{
	struct object *obj;

	obj = lookup_object(oid->hash);
	if (!obj)
		obj = parse_object(oid);

	/* Ignore remote objects that don't exist locally */
	if (!obj)
		return;

	obj->flags |= REMOTE;
	if (!object_list_contains(objects, obj))
		object_list_insert(obj, &objects);
}