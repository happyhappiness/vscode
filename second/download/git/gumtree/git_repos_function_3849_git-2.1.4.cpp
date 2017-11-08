static int is_workflow_triangular(struct remote *remote)
{
	struct remote *fetch_remote = remote_get(NULL);
	return (fetch_remote && fetch_remote != remote);
}