void avl_destroy (avl_tree_t *t)
{
	free_node (t->root);
	free (t);
}