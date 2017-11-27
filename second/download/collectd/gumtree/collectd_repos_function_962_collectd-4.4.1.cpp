static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}