static int is_per_worktree_ref(const char *refname)
{
	return !strcmp(refname, "HEAD");
}