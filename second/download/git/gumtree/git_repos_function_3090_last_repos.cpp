static void add_head_info(struct worktree *wt)
{
	int flags;
	const char *target;

	target = refs_resolve_ref_unsafe(get_worktree_ref_store(wt),
					 "HEAD",
					 RESOLVE_REF_READING,
					 wt->head_sha1, &flags);
	if (!target)
		return;

	if (flags & REF_ISSYMREF)
		wt->head_ref = xstrdup(target);
	else
		wt->is_detached = 1;
}