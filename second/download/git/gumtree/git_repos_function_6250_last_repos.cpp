static void add_family_to_write_order(struct object_entry **wo,
				      unsigned int *endp,
				      struct object_entry *e)
{
	struct object_entry *root;

	for (root = e; root->delta; root = root->delta)
		; /* nothing */
	add_descendants_to_write_order(wo, endp, root);
}