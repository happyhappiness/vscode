static int num_parents(struct commit *commit)
{
	struct commit_list *parents;
	int i;

	for (i = 0, parents = commit->parents;
	     parents;
	     parents = parents->next)
		i++;
	return i;
}