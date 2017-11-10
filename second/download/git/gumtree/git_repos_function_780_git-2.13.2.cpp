static inline void list_move(struct list_head *elem, struct list_head *head)
{
	__list_del(elem->prev, elem->next);
	list_add(elem, head);
}