/*
 * Called only from check_object() after it verified this object
 * is Ok.
 */
static void write_cached_object(struct object *obj, struct obj_buffer *obj_buf)
{
	unsigned char sha1[20];

	if (write_sha1_file(obj_buf->buffer, obj_buf->size, typename(obj->type), sha1) < 0)
		die("failed to write object %s", oid_to_hex(&obj->oid));
	obj->flags |= FLAG_WRITTEN;
}

/*
 * At the very end of the processing, write_rest() scans the objects
