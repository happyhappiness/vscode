llentry_t *llist_search (llist_t *l, const char *key)
{
	return (llist_search_custom (l, llist_strcmp, (void *)key));
}