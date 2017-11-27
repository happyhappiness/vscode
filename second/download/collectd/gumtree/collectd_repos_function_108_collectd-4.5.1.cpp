llentry_t *llist_head (llist_t *l)
{
	if (l == NULL)
		return (NULL);
	return (l->head);
}