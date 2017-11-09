static void pop_filter_list(filter_rule_list *listp)
{
	filter_rule *inherited;

	if (!listp->tail)
		return;

	inherited = listp->tail->next;

	/* Truncate any inherited items from the local list. */
	listp->tail->next = NULL;
	/* Now free everything that is left. */
	free_filters(listp->head);

	listp->head = inherited;
	listp->tail = NULL;
}