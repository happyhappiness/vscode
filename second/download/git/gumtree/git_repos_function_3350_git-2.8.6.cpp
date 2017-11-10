struct patch_id *add_commit_patch_id(struct commit *commit,
				     struct patch_ids *ids)
{
	return add_commit(commit, ids, 0);
}