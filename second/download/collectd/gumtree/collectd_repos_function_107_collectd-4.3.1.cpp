llentry_t *llist_search (llist_t *l, const char *key)
{
	llentry_t *e;

	for (e = l->head; e != NULL; e = e->next)
		if (strcmp (key, e->key) == 0)
			break;

	return (e);
}