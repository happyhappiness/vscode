static int check_tracking_branch(struct remote *remote, void *cb_data)
{
	char *tracking_branch = cb_data;
	struct refspec query;
	memset(&query, 0, sizeof(struct refspec));
	query.dst = tracking_branch;
	return !remote_find_tracking(remote, &query);
}