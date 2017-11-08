static inline void list_splice(struct list_head *add, struct list_head *head)
{
	/* Do nothing if the list which gets added is empty. */
	if (add != add->next) {
		add->next->prev = head;
		add->prev->next = head->next;
		head->next->prev = add->prev;
		head->next = add->next;
	}
}