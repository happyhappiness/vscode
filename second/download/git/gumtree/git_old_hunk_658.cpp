				   struct branch_info *new)
{
	struct strbuf msg = STRBUF_INIT;
	const char *old_desc, *reflog_msg;
	if (opts->new_branch) {
		if (opts->new_orphan_branch) {
			if (opts->new_branch_log && !log_all_ref_updates) {
				int ret;
				char *refname;
				struct strbuf err = STRBUF_INIT;

				refname = mkpathdup("refs/heads/%s", opts->new_orphan_branch);
				ret = safe_create_reflog(refname, 1, &err);
				free(refname);
				if (ret) {
					fprintf(stderr, _("Can not do reflog for '%s': %s\n"),
						opts->new_orphan_branch, err.buf);
					strbuf_release(&err);
					return;
				}
				strbuf_release(&err);
			}
		}
		else
			create_branch(opts->new_branch, new->name,
				      opts->new_branch_force ? 1 : 0,
				      opts->new_branch_log,
				      opts->new_branch_force ? 1 : 0,
