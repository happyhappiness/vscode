static void mark_object(struct object *obj, const char *name, void *data)
{
	update_progress(data);
}