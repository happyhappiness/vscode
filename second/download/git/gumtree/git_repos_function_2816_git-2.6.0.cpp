static int should_autocreate_reflog(const char *refname)
{
	if (!log_all_ref_updates)
		return 0;
	return starts_with(refname, "refs/heads/") ||
		starts_with(refname, "refs/remotes/") ||
		starts_with(refname, "refs/notes/") ||
		!strcmp(refname, "HEAD");
}