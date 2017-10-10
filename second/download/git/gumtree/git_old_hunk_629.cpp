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

