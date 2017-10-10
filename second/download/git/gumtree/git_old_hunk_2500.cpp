{
	struct strbuf msg = STRBUF_INIT;
	const char *old_desc, *reflog_msg;
	if (opts->new_branch) {
		if (opts->new_orphan_branch) {
			if (opts->new_branch_log && !log_all_ref_updates) {
				int temp;
				struct strbuf log_file = STRBUF_INIT;
				int ret;
				const char *ref_name;

				ref_name = mkpath("refs/heads/%s", opts->new_orphan_branch);
				temp = log_all_ref_updates;
				log_all_ref_updates = 1;
				ret = log_ref_setup(ref_name, &log_file);
				log_all_ref_updates = temp;
				strbuf_release(&log_file);
				if (ret) {
					fprintf(stderr, _("Can not do reflog for '%s'\n"),
					    opts->new_orphan_branch);
					return;
				}
			}
		}
		else
			create_branch(old->name, opts->new_branch, new->name,
				      opts->new_branch_force ? 1 : 0,
				      opts->new_branch_log,
