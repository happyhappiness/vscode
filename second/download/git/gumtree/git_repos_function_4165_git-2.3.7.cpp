static int switch_branches(const struct checkout_opts *opts,
			   struct branch_info *new)
{
	int ret = 0;
	struct branch_info old;
	void *path_to_free;
	unsigned char rev[20];
	int flag, writeout_error = 0;
	memset(&old, 0, sizeof(old));
	old.path = path_to_free = resolve_refdup("HEAD", 0, rev, &flag);
	old.commit = lookup_commit_reference_gently(rev, 1);
	if (!(flag & REF_ISSYMREF))
		old.path = NULL;

	if (old.path)
		skip_prefix(old.path, "refs/heads/", &old.name);

	if (!new->name) {
		new->name = "HEAD";
		new->commit = old.commit;
		if (!new->commit)
			die(_("You are on a branch yet to be born"));
		parse_commit_or_die(new->commit);
	}

	ret = merge_working_tree(opts, &old, new, &writeout_error);
	if (ret) {
		free(path_to_free);
		return ret;
	}

	if (!opts->quiet && !old.path && old.commit && new->commit != old.commit)
		orphaned_commit_warning(old.commit, new->commit);

	update_refs_for_switch(opts, &old, new);

	ret = post_checkout_hook(old.commit, new->commit, 1);
	free(path_to_free);
	return ret || writeout_error;
}