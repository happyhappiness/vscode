void mru_mark(struct mru *mru, struct mru_entry *entry)
{
	/* If we're already at the front of the list, nothing to do */
	if (mru->head == entry)
		return;

	/* Otherwise, remove us from our current slot... */
	if (entry->prev)
		entry->prev->next = entry->next;
	if (entry->next)
		entry->next->prev = entry->prev;
	else
		mru->tail = entry->prev;

	/* And insert us at the beginning. */
	entry->prev = NULL;
	entry->next = mru->head;
	if (mru->head)
		mru->head->prev = entry;
	mru->head = entry;
}