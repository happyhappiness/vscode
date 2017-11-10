static int remote_tracking(struct remote *remote, const char *refname,
			   struct object_id *oid)
{
	char *dst;

	dst = apply_refspecs(remote->fetch, remote->fetch_refspec_nr, refname);
	if (!dst)
		return -1; /* no tracking ref for refname at remote */
	if (read_ref(dst, oid->hash))
		return -1; /* we know what the tracking ref is but we cannot read it */
	return 0;
}