static struct tree_entry *new_tree_entry(void)
{
	struct tree_entry *e;

	if (!avail_tree_entry) {
		unsigned int n = tree_entry_alloc;
		total_allocd += n * sizeof(struct tree_entry);
		ALLOC_ARRAY(e, n);
		avail_tree_entry = e;
		while (n-- > 1) {
			*((void**)e) = e + 1;
			e++;
		}
		*((void**)e) = NULL;
	}

	e = avail_tree_entry;
	avail_tree_entry = *((void**)e);
	return e;
}