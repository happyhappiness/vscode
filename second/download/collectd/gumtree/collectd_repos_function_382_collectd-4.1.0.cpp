static avl_node_t *rotate_right_left (avl_tree_t *t, avl_node_t *x)
{
	rotate_right (t, x->right);
	return (rotate_left (t, x));
}