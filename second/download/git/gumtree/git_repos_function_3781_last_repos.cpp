static struct commit *make_virtual_commit(struct tree *tree, const char *comment)
{
	struct commit *commit = alloc_commit_node();

	set_merge_remote_desc(commit, comment, (struct object *)commit);
	commit->tree = tree;
	commit->object.parsed = 1;
	return commit;
}