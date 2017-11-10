static int mark_used(struct object *obj, int type, void *data)
{
	if (!obj)
		return 1;
	obj->used = 1;
	return 0;
}