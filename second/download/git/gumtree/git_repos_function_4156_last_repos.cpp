void free_tree_buffer(struct tree *tree)
{
	FREE_AND_NULL(tree->buffer);
	tree->size = 0;
	tree->object.parsed = 0;
}