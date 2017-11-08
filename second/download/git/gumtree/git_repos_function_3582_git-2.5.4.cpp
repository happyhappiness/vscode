static const char *tracking_for_push_dest(struct remote *remote,
					  const char *refname,
					  struct strbuf *err)
{
	char *ret;

	ret = apply_refspecs(remote->fetch, remote->fetch_refspec_nr, refname);
	if (!ret)
		return error_buf(err,
				 _("push destination '%s' on remote '%s' has no local tracking branch"),
				 refname, remote->name);
	return ret;
}