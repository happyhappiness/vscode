const struct git_attr *git_attr(const char *name)
{
	return git_attr_internal(name, strlen(name));
}