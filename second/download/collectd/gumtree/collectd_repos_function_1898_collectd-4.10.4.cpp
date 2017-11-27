static inline void list_del_rcu(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->prev = LIST_POISON2;
}