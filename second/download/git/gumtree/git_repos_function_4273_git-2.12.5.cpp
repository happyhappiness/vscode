static void show_commit(struct commit *commit, void *data)
{
	commit_list_insert(commit, data);
}