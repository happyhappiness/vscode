void llist_remove (llist_t *l, llentry_t *e)
{
	llentry_t *prev;

	if ((l == NULL) || (e == NULL))
		return;

	prev = l->head;
	while ((prev != NULL) && (prev->next != e))
		prev = prev->next;

	if (prev != NULL)
		prev->next = e->next;
	if (l->head == e)
		l->head = e->next;
	if (l->tail == e)
		l->tail = prev;

	--(l->size);
}