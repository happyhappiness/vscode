void c_avl_destroy (c_avl_tree_t *t)
{
	free_node (t->root);
	free (t);
}