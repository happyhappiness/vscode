void add_object(struct object *obj,
		struct object_array *p,
		struct name_path *path,
		const char *name)
{
	char *pn = path_name(path, name);
	add_object_array(obj, pn, p);
	free(pn);
}