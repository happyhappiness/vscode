void add_object_array_with_mode(struct object *obj, const char *name, struct object_array *array, unsigned mode)
{
	add_object_array_with_mode_context(obj, name, array, mode, NULL);
}