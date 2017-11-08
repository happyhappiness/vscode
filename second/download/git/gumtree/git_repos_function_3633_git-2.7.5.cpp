static int valid_remote(const struct remote *remote)
{
	return (!!remote->url) || (!!remote->foreign_vcs);
}