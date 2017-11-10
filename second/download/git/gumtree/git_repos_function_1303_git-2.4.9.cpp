void *alloc_tree_node(void)
{
	struct tree *t = alloc_node(&tree_state, sizeof(struct tree));
	t->object.type = OBJ_TREE;
	return t;
}