static void gc_boundary(struct object_array *array)
{
	if (array->nr == array->alloc)
		object_array_filter(array, entry_unshown, NULL);
}