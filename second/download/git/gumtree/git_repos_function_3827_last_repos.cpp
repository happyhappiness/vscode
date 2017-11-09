static struct commit_list *reverse_commit_list(struct commit_list *list)
{
	struct commit_list *next = NULL, *current, *backup;
	for (current = list; current; current = backup) {
		backup = current->next;
		current->next = next;
		next = current;
	}
	return next;
}