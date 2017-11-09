static void llist_free(struct llist *list)
{
	while ((list->back = list->front)) {
		list->front = list->front->next;
		llist_item_put(list->back);
	}
	free(list);
}