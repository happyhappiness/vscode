static struct blame_entry *blame_sort(struct blame_entry *head,
				      int (*compare_fn)(const void *, const void *))
{
	return llist_mergesort (head, get_next_blame, set_next_blame, compare_fn);
}