{
	if (!branch)
		die(_(message_detached_head_die), remote->name);
	add_refspec(branch->name);
}

static int is_workflow_triangular(struct remote *remote)
{
	struct remote *fetch_remote = remote_get(NULL);
	return (fetch_remote && fetch_remote != remote);
}

