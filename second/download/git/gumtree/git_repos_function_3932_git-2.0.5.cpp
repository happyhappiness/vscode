static void write_cached_object(struct object *obj)
{
	unsigned char sha1[20];
	struct obj_buffer *obj_buf = lookup_object_buffer(obj);
	if (write_sha1_file(obj_buf->buffer, obj_buf->size, typename(obj->type), sha1) < 0)
		die("failed to write object %s", sha1_to_hex(obj->sha1));
	obj->flags |= FLAG_WRITTEN;
}