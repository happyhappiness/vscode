static int count_parents(struct commit *commit)
{
	struct commit_list *parents = commit->parents;
	int count = 0;
	while (parents) {
		count++;
		parents = parents->next;
	}
	return count;
}