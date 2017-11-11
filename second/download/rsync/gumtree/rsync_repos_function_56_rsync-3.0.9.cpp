static void clear_filter_list(struct filter_list_struct *listp)
{
	if (listp->tail) {
		struct filter_struct *ent, *next;
		/* Truncate any inherited items from the local list. */
		listp->tail->next = NULL;
		/* Now free everything that is left. */
		for (ent = listp->head; ent; ent = next) {
			next = ent->next;
			free_filter(ent);
		}
	}

	listp->head = listp->tail = NULL;
}