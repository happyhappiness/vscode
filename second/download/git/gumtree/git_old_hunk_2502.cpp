		opts->track = git_branch_track;

	if (new->name && !new->commit)
		die(_("Cannot switch branch to a non-commit '%s'"),
		    new->name);

	if (new->path && !opts->force_detach && !opts->new_branch) {
		unsigned char sha1[20];
		int flag;
		char *head_ref = resolve_refdup("HEAD", 0, sha1, &flag);
		if (head_ref &&
		    (!(flag & REF_ISSYMREF) || strcmp(head_ref, new->path)) &&
		    !opts->ignore_other_worktrees)
			check_linked_checkouts(new);
		free(head_ref);
	}

	if (!new->commit && opts->new_branch) {
		unsigned char rev[20];
		int flag;
