struct commit_list **commit_list_append(struct commit *commit,
					struct commit_list **next)
{
	struct commit_list *new = xmalloc(sizeof(struct commit_list));
	new->item = commit;
	*next = new;
	new->next = NULL;
	return &new->next;
}