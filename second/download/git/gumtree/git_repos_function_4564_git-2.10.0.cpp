static int checkout_branch(struct checkout_opts *opts,
			   struct branch_info *new)
{
	if (opts->pathspec.nr)
		die(_("paths cannot be used with switching branches"));

	if (opts->patch_mode)
		die(_("'%s' cannot be used with switching branches"),
		    "--patch");

	if (opts->writeout_stage)
		die(_("'%s' cannot be used with switching branches"),
		    "--ours/--theirs");

	if (opts->force && opts->merge)
		die(_("'%s' cannot be used with '%s'"), "-f", "-m");

	if (opts->force_detach && opts->new_branch)
		die(_("'%s' cannot be used with '%s'"),
		    "--detach", "-b/-B/--orphan");

	if (opts->new_orphan_branch) {
		if (opts->track != BRANCH_TRACK_UNSPECIFIED)
			die(_("'%s' cannot be used with '%s'"), "--orphan", "-t");
	} else if (opts->force_detach) {
		if (opts->track != BRANCH_TRACK_UNSPECIFIED)
			die(_("'%s' cannot be used with '%s'"), "--detach", "-t");
	} else if (opts->track == BRANCH_TRACK_UNSPECIFIED)
		opts->track = git_branch_track;

	if (new->name && !new->commit)
		die(_("Cannot switch branch to a non-commit '%s'"),
		    new->name);

	if (new->path && !opts->force_detach && !opts->new_branch &&
	    !opts->ignore_other_worktrees) {
		unsigned char sha1[20];
		int flag;
		char *head_ref = resolve_refdup("HEAD", 0, sha1, &flag);
		if (head_ref &&
		    (!(flag & REF_ISSYMREF) || strcmp(head_ref, new->path)))
			die_if_checked_out(new->path, 1);
		free(head_ref);
	}

	if (!new->commit && opts->new_branch) {
		unsigned char rev[20];
		int flag;

		if (!read_ref_full("HEAD", 0, rev, &flag) &&
		    (flag & REF_ISSYMREF) && is_null_sha1(rev))
			return switch_unborn_to_new_branch(opts);
	}
	return switch_branches(opts, new);
}