{
	struct obj_buffer *obj;
	obj = xcalloc(1, sizeof(struct obj_buffer));
	obj->buffer = buffer;
	obj->size = size;
	if (add_decoration(&obj_decorate, object, obj))
		die("object %s tried to add buffer twice!", sha1_to_hex(object->sha1));
}

/*
 * Make sure at least "min" bytes are available in the buffer, and
 * return the pointer to the buffer.
 */
