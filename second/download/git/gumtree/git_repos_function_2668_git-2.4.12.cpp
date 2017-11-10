int delete_reflog(const char *refname)
{
	return remove_path(git_path("logs/%s", refname));
}