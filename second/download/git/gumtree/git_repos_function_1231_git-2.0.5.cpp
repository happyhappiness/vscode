void *alloc_tag_node(void)
{
	struct tag *t = alloc_node(&tag_state, sizeof(struct tag));
	t->object.type = OBJ_TAG;
	return t;
}