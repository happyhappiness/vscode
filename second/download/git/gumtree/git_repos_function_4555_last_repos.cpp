void mru_clear(struct mru *mru)
{
	struct mru_entry *p = mru->head;

	while (p) {
		struct mru_entry *to_free = p;
		p = p->next;
		free(to_free);
	}
	mru->head = mru->tail = NULL;
}