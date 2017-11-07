void add_object_array(struct object *obj, const char *name, struct object_array *array)
{
	add_object_array_with_mode(obj, name, array, S_IFINVALID);
}