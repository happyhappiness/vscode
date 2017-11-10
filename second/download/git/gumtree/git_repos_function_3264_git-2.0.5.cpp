static struct ref **tail_ref(struct ref **head)
{
	struct ref **tail = head;
	while (*tail)
		tail = &((*tail)->next);
	return tail;
}