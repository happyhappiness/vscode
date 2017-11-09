static inline void list_add_tail(struct list_head *newp, struct list_head *head)
{
	head->prev->next = newp;
	newp->next = head;
	newp->prev = head->prev;
	head->prev = newp;
}