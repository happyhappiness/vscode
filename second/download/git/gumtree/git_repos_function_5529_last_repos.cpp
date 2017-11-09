static void name_parent(struct commit *commit, struct commit *parent)
{
	struct commit_name *commit_name = commit->util;
	struct commit_name *parent_name = parent->util;
	if (!commit_name)
		return;
	if (!parent_name ||
	    commit_name->generation + 1 < parent_name->generation)
		name_commit(parent, commit_name->head_name,
			    commit_name->generation + 1);
}