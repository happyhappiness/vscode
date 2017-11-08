static void mark_object_reachable(struct object *obj)
{
	mark_object(obj, OBJ_ANY, NULL, NULL);
}