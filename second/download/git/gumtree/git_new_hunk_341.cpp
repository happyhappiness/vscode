	if (new->name && !new->commit)
		die(_("Cannot switch branch to a non-commit '%s'"),
		    new->name);

	if (new->path && !opts->force_detach && !opts->new_branch &&
	    !opts->ignore_other_worktrees) {
		struct object_id oid;
		int flag;
		char *head_ref = resolve_refdup("HEAD", 0, oid.hash, &flag);
		if (head_ref &&
		    (!(flag & REF_ISSYMREF) || strcmp(head_ref, new->path)))
			die_if_checked_out(new->path, 1);
		free(head_ref);
	}

	if (!new->commit && opts->new_branch) {
		struct object_id rev;
		int flag;

		if (!read_ref_full("HEAD", 0, rev.hash, &flag) &&
		    (flag & REF_ISSYMREF) && is_null_oid(&rev))
			return switch_unborn_to_new_branch(opts);
	}
	return switch_branches(opts, new);
}

int cmd_checkout(int argc, const char **argv, const char *prefix)
