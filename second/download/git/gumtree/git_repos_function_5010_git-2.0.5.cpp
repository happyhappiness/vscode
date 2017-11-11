static void show_object(struct object *obj,
			const struct name_path *path, const char *last,
			void *data)
{
	char *name = path_name(path, last);

	add_preferred_base_object(name);
	add_object_entry(obj->sha1, obj->type, name, 0);
	obj->flags |= OBJECT_ADDED;

	/*
	 * We will have generated the hash from the name,
	 * but not saved a pointer to it - we can free it
	 */
	free((char *)name);
}