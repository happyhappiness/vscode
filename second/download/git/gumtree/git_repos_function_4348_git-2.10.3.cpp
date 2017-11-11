static const char *get_upstream_branch(const char *remote)
{
	struct remote *rm;
	struct branch *curr_branch;
	const char *curr_branch_remote;

	rm = remote_get(remote);
	if (!rm)
		return NULL;

	curr_branch = branch_get("HEAD");
	if (!curr_branch)
		return NULL;

	curr_branch_remote = remote_for_branch(curr_branch, NULL);
	assert(curr_branch_remote);

	if (strcmp(curr_branch_remote, rm->name))
		return NULL;

	return branch_get_upstream(curr_branch, NULL);
}