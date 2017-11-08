int remote_is_configured(struct remote *remote)
{
	return remote && remote->origin;
}