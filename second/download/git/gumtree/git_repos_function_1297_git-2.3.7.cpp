void *alloc_object_node(void)
{
	struct object *obj = alloc_node(&object_state, sizeof(union any_object));
	obj->type = OBJ_NONE;
	return obj;
}