{
	struct mtree_entry *np;

	if (parent == NULL)
		return (NULL);
	np = (struct mtree_entry *)__archive_rb_tree_find_node(
	    &(parent->dir_info->rbtree), child_name);
	return (np);
}