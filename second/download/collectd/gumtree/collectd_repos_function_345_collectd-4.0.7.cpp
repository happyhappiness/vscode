static avl_node_t *rotate_left_right (avl_tree_t *t, avl_node_t *x)
{
	rotate_left (t, x->left);
	return (rotate_right (t, x));
}