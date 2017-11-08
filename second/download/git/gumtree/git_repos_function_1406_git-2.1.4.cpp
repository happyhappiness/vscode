void add_object_array_with_context(struct object *obj, const char *name, struct object_array *array, struct object_context *context)
{
	if (context)
		add_object_array_with_mode_context(obj, name, array, context->mode, context);
	else
		add_object_array_with_mode_context(obj, name, array, S_IFINVALID, context);
}