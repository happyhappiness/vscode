static void one_remote_object(const char *hex)
{
	unsigned char sha1[20];
	struct object *obj;

	if (get_sha1_hex(hex, sha1) != 0)
		return;

	obj = lookup_object(sha1);
	if (!obj)
		obj = parse_object(sha1);

	/* Ignore remote objects that don't exist locally */
	if (!obj)
		return;

	obj->flags |= REMOTE;
	if (!object_list_contains(objects, obj))
		object_list_insert(obj, &objects);
}