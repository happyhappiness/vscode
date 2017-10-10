{
	if (!branch || i < 0 || i >= branch->merge_nr)
		return 0;
	return refname_match(branch->merge[i]->src, refname);
}

__attribute((format (printf,2,3)))
static const char *error_buf(struct strbuf *err, const char *fmt, ...)
{
	if (err) {
		va_list ap;
		va_start(ap, fmt);
		strbuf_vaddf(err, fmt, ap);
		va_end(ap);
	}
	return NULL;
}

const char *branch_get_upstream(struct branch *branch, struct strbuf *err)
{
	if (!branch)
		return error_buf(err, _("HEAD does not point to a branch"));

	if (!branch->merge || !branch->merge[0]) {
		/*
		 * no merge config; is it because the user didn't define any,
		 * or because it is not a real branch, and get_branch
		 * auto-vivified it?
		 */
		if (!ref_exists(branch->refname))
			return error_buf(err, _("no such branch: '%s'"),
					 branch->name);
		return error_buf(err,
				 _("no upstream configured for branch '%s'"),
				 branch->name);
	}

	if (!branch->merge[0]->dst)
		return error_buf(err,
				 _("upstream branch '%s' not stored as a remote-tracking branch"),
				 branch->merge[0]->src);

	return branch->merge[0]->dst;
}

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

const char *branch_get_push(struct branch *branch, struct strbuf *err)
{
	if (!branch->push_tracking_ref)
		branch->push_tracking_ref = branch_get_push_1(branch, err);
	return branch->push_tracking_ref;
}

static int ignore_symref_update(const char *refname)
{
	unsigned char sha1[20];
	int flag;

	if (!resolve_ref_unsafe(refname, 0, sha1, &flag))
