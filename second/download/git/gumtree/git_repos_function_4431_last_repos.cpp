struct remote *remote_get(const char *name)
{
	return remote_get_1(name, remote_for_branch);
}