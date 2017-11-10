static int contains_name(struct object_array *array, const char *name)
{
	unsigned nr = array->nr, i;
	struct object_array_entry *object = array->objects;

	for (i = 0; i < nr; i++, object++)
		if (!strcmp(object->name, name))
			return 1;
	return 0;
}