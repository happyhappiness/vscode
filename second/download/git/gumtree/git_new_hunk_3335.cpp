	for (i = 0; i < array.nr; i++)
		format_and_print_ref_item(array.items[i], maxwidth, filter, remote_prefix);

	ref_array_clear(&array);
}

static void reject_rebase_or_bisect_branch(const char *target)
{
	struct worktree **worktrees = get_worktrees();
	int i;

	for (i = 0; worktrees[i]; i++) {
		struct worktree *wt = worktrees[i];

		if (!wt->is_detached)
			continue;

		if (is_worktree_being_rebased(wt, target))
			die(_("Branch %s is being rebased at %s"),
			    target, wt->path);

		if (is_worktree_being_bisected(wt, target))
			die(_("Branch %s is being bisected at %s"),
			    target, wt->path);
	}

	free_worktrees(worktrees);
}

static void rename_branch(const char *oldname, const char *newname, int force)
{
	struct strbuf oldref = STRBUF_INIT, newref = STRBUF_INIT, logmsg = STRBUF_INIT;
	struct strbuf oldsection = STRBUF_INIT, newsection = STRBUF_INIT;
	int recovery = 0;
	int clobber_head_ok;
