static void write_cached_object(struct object *obj, struct obj_buffer *obj_buf)
{
	struct object_id oid;

	if (write_sha1_file(obj_buf->buffer, obj_buf->size, typename(obj->type), oid.hash) < 0)
		die("failed to write object %s", oid_to_hex(&obj->oid));
	obj->flags |= FLAG_WRITTEN;
}