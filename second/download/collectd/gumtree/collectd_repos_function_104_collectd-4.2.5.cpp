void llist_prepend (llist_t *l, llentry_t *e)
{
	e->next = l->head;
	l->head = e;

	if (l->tail == NULL)
		l->tail = e;
}