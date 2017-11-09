static inline void list_replace(struct list_head *old, struct list_head *newp)
{
	newp->next = old->next;
	newp->prev = old->prev;
	newp->prev->next = newp;
	newp->next->prev = newp;
}