static inline void list_del(struct list_head *elem)
{
	__list_del(elem->prev, elem->next);
}