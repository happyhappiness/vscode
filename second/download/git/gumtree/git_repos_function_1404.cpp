void *alloc_commit_node(void)
{
	struct commit *c = alloc_node(&commit_state, sizeof(struct commit));
	c->object.type = OBJ_COMMIT;
	c->index = alloc_commit_index();
	return c;
}