static int check_object(struct object *obj, int type, void *data)
{
	if (!obj)
		return 1;

	if (obj->flags & FLAG_WRITTEN)
		return 0;

	if (type != OBJ_ANY && obj->type != type)
		die("object type mismatch");

	if (!(obj->flags & FLAG_OPEN)) {
		unsigned long size;
		int type = sha1_object_info(obj->sha1, &size);
		if (type != obj->type || type <= 0)
			die("object of unexpected type");
		obj->flags |= FLAG_WRITTEN;
		return 0;
	}

	if (fsck_object(obj, 1, fsck_error_function))
		die("Error in object");
	if (fsck_walk(obj, check_object, NULL))
		die("Error on reachable objects of %s", sha1_to_hex(obj->sha1));
	write_cached_object(obj);
	return 0;
}