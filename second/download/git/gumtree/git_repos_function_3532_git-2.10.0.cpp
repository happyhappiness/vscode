void free_tree_buffer(struct tree *tree)
{
	free(tree->buffer);
	tree->buffer = NULL;
	tree->size = 0;
	tree->object.parsed = 0;
}