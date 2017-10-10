static unsigned nr_objects;

/*
 * Called only from check_object() after it verified this object
 * is Ok.
 */
static void write_cached_object(struct object *obj)
{
	unsigned char sha1[20];
	struct obj_buffer *obj_buf = lookup_object_buffer(obj);
	if (write_sha1_file(obj_buf->buffer, obj_buf->size, typename(obj->type), sha1) < 0)
		die("failed to write object %s", sha1_to_hex(obj->sha1));
	obj->flags |= FLAG_WRITTEN;
}

/*
 * At the very end of the processing, write_rest() scans the objects
 * that have reachability requirements and calls this function.
 * Verify its reachability and validity recursively and write it out.
 */
static int check_object(struct object *obj, int type, void *data)
{
	if (!obj)
		return 1;

	if (obj->flags & FLAG_WRITTEN)
		return 0;

