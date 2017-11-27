static avl_node_t *rotate_left (avl_tree_t *t, avl_node_t *x)
{
	avl_node_t *p;
	avl_node_t *y;
	avl_node_t *b;

	p = x->parent;
	y = x->right;
	b = y->left;

	x->right = b;
	if (b != NULL)
		b->parent = x;

	x->parent = y;
	y->left = x;

	y->parent = p;
	assert ((p == NULL) || (p->left == x) || (p->right == x));
	if (p == NULL)
		t->root = y;
	else if (p->left == x)
		p->left = y;
	else
		p->right = y;

	x->height = calc_height (x);
	y->height = calc_height (y);

	return (y);
}