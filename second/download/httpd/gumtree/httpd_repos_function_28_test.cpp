void free_commit_list(struct commit_list *list)
{
	while (list)
		pop_commit(&list);
}