static struct commit *make_virtual_commit(struct tree *tree, const char *comment)
{
	struct commit *commit = alloc_commit_node();
	struct merge_remote_desc *desc = xmalloc(sizeof(*desc));

	desc->name = comment;
	desc->obj = (struct object *)commit;
	commit->tree = tree;
	commit->util = desc;
	commit->object.parsed = 1;
	return commit;
}