}

static const char *branch_get_push_1(struct branch *branch, struct strbuf *err)
{
	struct remote *remote;

	remote = remote_get(pushremote_for_branch(branch, NULL));
	if (!remote)
		return error_buf(err,
				 _("branch '%s' has no remote for pushing"),
				 branch->name);

