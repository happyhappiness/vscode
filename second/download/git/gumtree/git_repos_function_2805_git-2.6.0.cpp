enum ref_type ref_type(const char *refname)
{
	if (is_per_worktree_ref(refname))
		return REF_TYPE_PER_WORKTREE;
	if (is_pseudoref_syntax(refname))
		return REF_TYPE_PSEUDOREF;
       return REF_TYPE_NORMAL;
}