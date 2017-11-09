static int traverse_one_object(struct object *obj)
{
	return fsck_walk(obj, obj, &fsck_walk_options);
}