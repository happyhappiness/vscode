static const char *branch_get_push_1(struct branch *branch, struct strbuf *err)
{
	struct remote *remote;

	if (!branch)
		return error_buf(err, _("HEAD does not point to a branch"));

	remote = remote_get(pushremote_for_branch(branch, NULL));
	if (!remote)
		return error_buf(err,
				 _("branch '%s' has no remote for pushing"),
				 branch->name);

	if (remote->push_refspec_nr) {
		char *dst;
		const char *ret;

		dst = apply_refspecs(remote->push, remote->push_refspec_nr,
				     branch->refname);
		if (!dst)
			return error_buf(err,
					 _("push refspecs for '%s' do not include '%s'"),
					 remote->name, branch->name);

		ret = tracking_for_push_dest(remote, dst, err);
		free(dst);
		return ret;
	}

	if (remote->mirror)
		return tracking_for_push_dest(remote, branch->refname, err);

	switch (push_default) {
	case PUSH_DEFAULT_NOTHING:
		return error_buf(err, _("push has no destination (push.default is 'nothing')"));

	case PUSH_DEFAULT_MATCHING:
	case PUSH_DEFAULT_CURRENT:
		return tracking_for_push_dest(remote, branch->refname, err);

	case PUSH_DEFAULT_UPSTREAM:
		return branch_get_upstream(branch, err);

	case PUSH_DEFAULT_UNSPECIFIED:
	case PUSH_DEFAULT_SIMPLE:
		{
			const char *up, *cur;

			up = branch_get_upstream(branch, err);
			if (!up)
				return NULL;
			cur = tracking_for_push_dest(remote, branch->refname, err);
			if (!cur)
				return NULL;
			if (strcmp(cur, up))
				return error_buf(err,
						 _("cannot resolve 'simple' push to a single destination"));
			return cur;
		}
	}

	die("BUG: unhandled push situation");
}