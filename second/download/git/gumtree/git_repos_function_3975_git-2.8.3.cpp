static int note_tree_consolidate(struct int_node *tree,
	struct int_node *parent, unsigned char index)
{
	unsigned int i;
	void *p = NULL;

	assert(tree && parent);
	assert(CLR_PTR_TYPE(parent->a[index]) == tree);

	for (i = 0; i < 16; i++) {
		if (GET_PTR_TYPE(tree->a[i]) != PTR_TYPE_NULL) {
			if (p) /* more than one entry */
				return -2;
			p = tree->a[i];
		}
	}

	/* replace tree with p in parent[index] */
	parent->a[index] = p;
	free(tree);
	return 0;
}