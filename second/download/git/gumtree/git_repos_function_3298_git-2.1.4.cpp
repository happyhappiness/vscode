int remote_find_tracking(struct remote *remote, struct refspec *refspec)
{
	return query_refspecs(remote->fetch, remote->fetch_refspec_nr, refspec);
}