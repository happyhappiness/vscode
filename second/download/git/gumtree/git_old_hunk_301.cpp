	/* Determine parents */
	reflog_msg = getenv("GIT_REFLOG_ACTION");
	if (!current_head) {
		if (!reflog_msg)
			reflog_msg = "commit (initial)";
	} else if (amend) {
		struct commit_list *c;

		if (!reflog_msg)
			reflog_msg = "commit (amend)";
		for (c = current_head->parents; c; c = c->next)
			pptr = &commit_list_insert(c->item, pptr)->next;
	} else if (whence == FROM_MERGE) {
		struct strbuf m = STRBUF_INIT;
		FILE *fp;
		int allow_fast_forward = 1;

		if (!reflog_msg)
			reflog_msg = "commit (merge)";
		pptr = &commit_list_insert(current_head, pptr)->next;
		fp = fopen(git_path_merge_head(), "r");
		if (fp == NULL)
			die_errno(_("could not open '%s' for reading"),
				  git_path_merge_head());
		while (strbuf_getline_lf(&m, fp) != EOF) {
			struct commit *parent;

			parent = get_merge_parent(m.buf);
			if (!parent)
				die(_("Corrupt MERGE_HEAD file (%s)"), m.buf);
			pptr = &commit_list_insert(parent, pptr)->next;
		}
		fclose(fp);
		strbuf_release(&m);
		if (!stat(git_path_merge_mode(), &statbuf)) {
			if (strbuf_read_file(&sb, git_path_merge_mode(), 0) < 0)
				die_errno(_("could not read MERGE_MODE"));
