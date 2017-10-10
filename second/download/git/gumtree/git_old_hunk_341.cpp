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

int cmd_checkout(int argc, const char **argv, const char *prefix)
