static void name_commit(struct commit *commit, const char *head_name, int nth)
{
	struct commit_name *name;
	if (!commit->util)
		commit->util = xmalloc(sizeof(struct commit_name));
	name = commit->util;
	name->head_name = head_name;
	name->generation = nth;
}