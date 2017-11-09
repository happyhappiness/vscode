int remote_is_configured(struct remote *remote, int in_repo)
{
	if (!remote)
		return 0;
	if (in_repo)
		return remote->configured_in_repo;
	return !!remote->origin;
}