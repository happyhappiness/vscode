struct commit_list *copy_commit_list(struct commit_list *list)
{
	struct commit_list *head = NULL;
	struct commit_list **pp = &head;
	while (list) {
		struct commit_list *new;
		new = xmalloc(sizeof(struct commit_list));
		new->item = list->item;
		new->next = NULL;
		*pp = new;
		pp = &new->next;
		list = list->next;
	}
	return head;
}