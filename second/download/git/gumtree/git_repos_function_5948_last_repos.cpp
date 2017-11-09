static inline struct llist_item *llist_item_get(void)
{
	struct llist_item *new;
	if ( free_nodes ) {
		new = free_nodes;
		free_nodes = free_nodes->next;
	} else {
		int i = 1;
		ALLOC_ARRAY(new, BLKSIZE);
		for (; i < BLKSIZE; i++)
			llist_item_put(&new[i]);
	}
	return new;
}