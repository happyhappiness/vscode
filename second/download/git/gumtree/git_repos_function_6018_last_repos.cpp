static void finish_commit(struct commit *commit, void *data)
{
	if (commit->parents) {
		free_commit_list(commit->parents);
		commit->parents = NULL;
	}
	free_commit_buffer(commit);
}