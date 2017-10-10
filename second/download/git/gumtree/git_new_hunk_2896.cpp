{
	struct obj_buffer *obj;
	obj = xcalloc(1, sizeof(struct obj_buffer));
	obj->buffer = buffer;
	obj->size = size;
	if (add_decoration(&obj_decorate, object, obj))
		die("object %s tried to add buffer twice!", oid_to_hex(&object->oid));
}

/*
 * Make sure at least "min" bytes are available in the buffer, and
 * return the pointer to the buffer.
 */
