struct remote *pushremote_get(const char *name)
{
	return remote_get_1(name, pushremote_for_branch);
}