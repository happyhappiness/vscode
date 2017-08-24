{
	if (!__archive_rb_tree_insert_node(
	    &(parent->rbtree), (struct archive_rb_node *)child))
		return (0);
	child->chnext = NULL;
	*parent->children.last = child;
	parent->children.last = &(child->chnext);
	child->parent = parent;
	return (1);
}