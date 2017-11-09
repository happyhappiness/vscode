static void llist_sorted_difference_inplace(struct llist *A,
				     struct llist *B)
{
	struct llist_item *hint, *b;

	hint = NULL;
	b = B->front;

	while (b) {
		hint = llist_sorted_remove(A, b->sha1, hint);
		b = b->next;
	}
}