static inline int list_empty(struct list_head *head)
{
	return head == head->next;
}