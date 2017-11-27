llentry_t *llist_search_custom (llist_t *l,
		int (*compare) (llentry_t *, void *), void *user_data)
{
	llentry_t *e;

	if (l == NULL)
		return (NULL);

	e = l->head;
	while (e != NULL) {
		llentry_t *next = e->next;

		if (compare (e, user_data) == 0)
			break;

		e = next;
	}

	return (e);
}