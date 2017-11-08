static int fsck_walk_commit(struct commit *commit, fsck_walk_func walk, void *data)
{
	struct commit_list *parents;
	int res;
	int result;

	if (parse_commit(commit))
		return -1;

	result = walk((struct object *)commit->tree, OBJ_TREE, data);
	if (result < 0)
		return result;
	res = result;

	parents = commit->parents;
	while (parents) {
		result = walk((struct object *)parents->item, OBJ_COMMIT, data);
		if (result < 0)
			return result;
		if (!res)
			res = result;
		parents = parents->next;
	}
	return res;
}