struct ref_store *get_worktree_ref_store(const struct worktree *wt)
{
	struct ref_store *refs;
	const char *id;

	if (wt->is_current)
		return get_main_ref_store();

	id = wt->id ? wt->id : "/";
	refs = lookup_ref_store_map(&worktree_ref_stores, id);
	if (refs)
		return refs;

	if (wt->id)
		refs = ref_store_init(git_common_path("worktrees/%s", wt->id),
				      REF_STORE_ALL_CAPS);
	else
		refs = ref_store_init(get_git_common_dir(),
				      REF_STORE_ALL_CAPS);

	if (refs)
		register_ref_store_map(&worktree_ref_stores, "worktree",
				       refs, id);
	return refs;
}