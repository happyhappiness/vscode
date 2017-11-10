void sort_ref_list(struct ref **l, int (*cmp)(const void *, const void *))
{
	*l = llist_mergesort(*l, ref_list_get_next, ref_list_set_next, cmp);
}