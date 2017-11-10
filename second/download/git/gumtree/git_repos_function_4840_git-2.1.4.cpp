static int is_superset(struct pack_list *pl, struct llist *list)
{
	struct llist *diff;

	diff = llist_copy(list);

	while (pl) {
		llist_sorted_difference_inplace(diff, pl->all_objects);
		if (diff->size == 0) { /* we're done */
			llist_free(diff);
			return 1;
		}
		pl = pl->next;
	}
	llist_free(diff);
	return 0;
}