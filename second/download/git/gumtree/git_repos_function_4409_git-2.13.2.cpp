void mru_append(struct mru *mru, void *item)
{
	struct mru_entry *cur = xmalloc(sizeof(*cur));
	cur->item = item;
	cur->prev = mru->tail;
	cur->next = NULL;

	if (mru->tail)
		mru->tail->next = cur;
	else
		mru->head = cur;
	mru->tail = cur;
}