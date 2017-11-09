int is_branch(const char *refname)
{
	return !strcmp(refname, "HEAD") || starts_with(refname, "refs/heads/");
}