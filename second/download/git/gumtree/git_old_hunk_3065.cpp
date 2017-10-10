		die(_("No current branch."));
	if (!branch->remote_name)
		die(_("No remote for the current branch."));
	if (!branch->merge_nr)
		die(_("No default upstream defined for the current branch."));

	args = xcalloc(branch->merge_nr + 1, sizeof(char *));
	for (i = 0; i < branch->merge_nr; i++) {
		if (!branch->merge[i]->dst)
			die(_("No remote-tracking branch for %s from %s"),
			    branch->merge[i]->src, branch->remote_name);
		args[i] = branch->merge[i]->dst;
	}
