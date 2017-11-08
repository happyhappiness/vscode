static int remote_tracking(struct remote *remote, const char *refname,
			   unsigned char sha1[20])
{
	char *dst;

	dst = apply_refspecs(remote->fetch, remote->fetch_refspec_nr, refname);
	if (!dst)
		return -1; /* no tracking ref for refname at remote */
	if (read_ref(dst, sha1))
		return -1; /* we know what the tracking ref is but we cannot read it */
	return 0;
}