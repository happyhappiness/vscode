static void resolve_base(struct object_entry *obj)
{
	struct base_data *base_obj = alloc_base_data();
	base_obj->obj = obj;
	base_obj->data = NULL;
	find_unresolved_deltas(base_obj);
}