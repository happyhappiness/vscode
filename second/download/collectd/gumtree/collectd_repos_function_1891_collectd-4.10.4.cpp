static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}