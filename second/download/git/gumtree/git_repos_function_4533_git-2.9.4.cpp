static int check_object(struct object *obj, int type, void *data, struct fsck_options *options)
{
	struct obj_buffer *obj_buf;

	if (!obj)
		return 1;

	if (obj->flags & FLAG_WRITTEN)
		return 0;

	if (type != OBJ_ANY && obj->type != type)
		die("object type mismatch");

	if (!(obj->flags & FLAG_OPEN)) {
		unsigned long size;
		int type = sha1_object_info(obj->oid.hash, &size);
		if (type != obj->type || type <= 0)
			die("object of unexpected type");
		obj->flags |= FLAG_WRITTEN;
		return 0;
	}

	obj_buf = lookup_object_buffer(obj);
	if (!obj_buf)
		die("Whoops! Cannot find object '%s'", oid_to_hex(&obj->oid));
	if (fsck_object(obj, obj_buf->buffer, obj_buf->size, &fsck_options))
		die("Error in object");
	fsck_options.walk = check_object;
	if (fsck_walk(obj, NULL, &fsck_options))
		die("Error on reachable objects of %s", oid_to_hex(&obj->oid));
	write_cached_object(obj, obj_buf);
	return 0;
}