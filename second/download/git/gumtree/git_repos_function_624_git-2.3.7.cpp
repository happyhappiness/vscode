void free_commit_list(struct commit_list *list)
{
	while (list) {
		struct commit_list *temp = list;
		list = temp->next;
		free(temp);
	}
}