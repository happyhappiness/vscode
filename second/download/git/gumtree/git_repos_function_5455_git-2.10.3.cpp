static inline struct llist_item *llist_insert(struct llist *list,
					      struct llist_item *after,
					       const unsigned char *sha1)
{
	struct llist_item *new = llist_item_get();
	new->sha1 = sha1;
	new->next = NULL;

	if (after != NULL) {
		new->next = after->next;
		after->next = new;
		if (after == list->back)
			list->back = new;
	} else {/* insert in front */
		if (list->size == 0)
			list->back = new;
		else
			new->next = list->front;
		list->front = new;
	}
	list->size++;
	return new;
}