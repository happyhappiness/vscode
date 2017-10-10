	struct branch *branch = branch_get(NULL);
	int i;
	const char **args;

	if (!branch)
		die(_("No current branch."));
	if (!branch->remote_name)
		die(_("No remote for the current branch."));
	if (!branch->merge_nr)
		die(_("No default upstream defined for the current branch."));

	args = xcalloc(branch->merge_nr + 1, sizeof(char *));
	for (i = 0; i < branch->merge_nr; i++) {
