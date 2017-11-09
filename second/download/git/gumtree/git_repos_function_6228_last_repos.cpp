static int setup_with_upstream(const char ***argv)
{
	struct branch *branch = branch_get(NULL);
	int i;
	const char **args;

	if (!branch)
		die(_("No current branch."));
	if (!branch->remote_name)
		die(_("No remote for the current branch."));
	if (!branch->merge_nr)
		die(_("No default upstream defined for the current branch."));

	args = xcalloc(st_add(branch->merge_nr, 1), sizeof(char *));
	for (i = 0; i < branch->merge_nr; i++) {
		if (!branch->merge[i]->dst)
			die(_("No remote-tracking branch for %s from %s"),
			    branch->merge[i]->src, branch->remote_name);
		args[i] = branch->merge[i]->dst;
	}
	args[i] = NULL;
	*argv = args;
	return i;
}