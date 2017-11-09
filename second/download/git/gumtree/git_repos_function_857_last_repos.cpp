static inline void list_add(struct list_head *newp, struct list_head *head)
{
	head->next->prev = newp;
	newp->next = head->next;
	newp->prev = head;
	head->next = newp;
}