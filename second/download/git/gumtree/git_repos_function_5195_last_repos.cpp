static struct obj_buffer *lookup_object_buffer(struct object *base)
{
	return lookup_decoration(&obj_decorate, base);
}