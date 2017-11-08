static struct llist * llist_copy(struct llist *list)
{
	struct llist *ret;
	struct llist_item *new, *old, *prev;

	llist_init(&ret);

	if ((ret->size = list->size) == 0)
		return ret;

	new = ret->front = llist_item_get();
	new->sha1 = list->front->sha1;

	old = list->front->next;
	while (old) {
		prev = new;
		new = llist_item_get();
		prev->next = new;
		new->sha1 = old->sha1;
		old = old->next;
	}
	new->next = NULL;
	ret->back = new;

	return ret;
}