const char *prettify_refname(const char *name)
{
	if (skip_prefix(name, "refs/heads/", &name) ||
	    skip_prefix(name, "refs/tags/", &name) ||
	    skip_prefix(name, "refs/remotes/", &name))
		; /* nothing */
	return name;
}