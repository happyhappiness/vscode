static c_avl_node_t *rotate_left_right (c_avl_tree_t *t, c_avl_node_t *x)
{
	rotate_left (t, x->left);
	return (rotate_right (t, x));
}