static int merge_abort(struct notes_merge_options *o)
{
	int ret = 0;

	/*
	 * Remove .git/NOTES_MERGE_PARTIAL and .git/NOTES_MERGE_REF, and call
	 * notes_merge_abort() to remove .git/NOTES_MERGE_WORKTREE.
	 */

	if (delete_ref(NULL, "NOTES_MERGE_PARTIAL", NULL, 0))
		ret += error(_("failed to delete ref NOTES_MERGE_PARTIAL"));
	if (delete_ref(NULL, "NOTES_MERGE_REF", NULL, REF_NODEREF))
		ret += error(_("failed to delete ref NOTES_MERGE_REF"));
	if (notes_merge_abort(o))
		ret += error(_("failed to remove 'git notes merge' worktree"));
	return ret;
}