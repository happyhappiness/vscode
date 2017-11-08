static struct blame_entry *reverse_blame(struct blame_entry *head,
					 struct blame_entry *tail)
{
	while (head) {
		struct blame_entry *next = head->next;
		head->next = tail;
		tail = head;
		head = next;
	}
	return tail;
}