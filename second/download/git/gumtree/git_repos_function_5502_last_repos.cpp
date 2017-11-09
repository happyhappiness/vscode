static int mark_used(struct object *obj, int type, void *data, struct fsck_options *options)
{
	if (!obj)
		return 1;
	obj->flags |= USED;
	return 0;
}