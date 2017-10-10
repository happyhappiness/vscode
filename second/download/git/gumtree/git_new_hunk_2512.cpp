		FILE *fp;
		int allow_fast_forward = 1;

		if (!reflog_msg)
			reflog_msg = "commit (merge)";
		pptr = &commit_list_insert(current_head, pptr)->next;
		fp = fopen(git_path_merge_head(), "r");
		if (fp == NULL)
			die_errno(_("could not open '%s' for reading"),
				  git_path_merge_head());
		while (strbuf_getline(&m, fp, '\n') != EOF) {
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
			if (!strcmp(sb.buf, "no-ff"))
				allow_fast_forward = 0;
		}
		if (allow_fast_forward)
			parents = reduce_heads(parents);
