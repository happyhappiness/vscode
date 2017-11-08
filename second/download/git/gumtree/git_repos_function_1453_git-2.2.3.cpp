void object_array_remove_duplicates(struct object_array *array)
{
	unsigned nr = array->nr, src;
	struct object_array_entry *objects = array->objects;

	array->nr = 0;
	for (src = 0; src < nr; src++) {
		if (!contains_name(array, objects[src].name)) {
			if (src != array->nr)
				objects[array->nr] = objects[src];
			array->nr++;
		} else {
			object_array_release_entry(&objects[src]);
		}
	}
}