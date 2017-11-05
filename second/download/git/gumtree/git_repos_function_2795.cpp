const char *prettify_refname(const char *name)
{
	return name + (
		starts_with(name, "refs/heads/") ? 11 :
		starts_with(name, "refs/tags/") ? 10 :
		starts_with(name, "refs/remotes/") ? 13 :
		0);
}