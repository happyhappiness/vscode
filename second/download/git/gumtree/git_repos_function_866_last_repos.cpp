static inline void list_replace_init(struct list_head *old,
				     struct list_head *newp)
{
	struct list_head *head = old->next;

	list_del(old);
	list_add_tail(newp, head);
	INIT_LIST_HEAD(old);
}