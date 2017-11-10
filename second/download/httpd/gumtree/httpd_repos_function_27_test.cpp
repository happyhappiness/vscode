struct commit_list *copy_commit_list(struct commit_list *list)
{
	struct commit_list *head = NULL;
	struct commit_list **pp = &head;
	while (list) {
		pp = commit_list_append(list->item, pp);
		list = list->next;
	}
	return head;
}