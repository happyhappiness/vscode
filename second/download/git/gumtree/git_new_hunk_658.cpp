				   struct branch_info *new)
{
	struct strbuf msg = STRBUF_INIT;
	const char *old_desc, *reflog_msg;
	if (opts->new_branch) {
		if (opts->new_orphan_branch) {
			char *refname;

			refname = mkpathdup("refs/heads/%s", opts->new_orphan_branch);
			if (opts->new_branch_log &&
			    !should_autocreate_reflog(refname)) {
				int ret;
				struct strbuf err = STRBUF_INIT;

				ret = safe_create_reflog(refname, 1, &err);
				if (ret) {
					fprintf(stderr, _("Can not do reflog for '%s': %s\n"),
						opts->new_orphan_branch, err.buf);
					strbuf_release(&err);
					free(refname);
					return;
				}
				strbuf_release(&err);
			}
			free(refname);
		}
		else
			create_branch(opts->new_branch, new->name,
				      opts->new_branch_force ? 1 : 0,
				      opts->new_branch_log,
				      opts->new_branch_force ? 1 : 0,
