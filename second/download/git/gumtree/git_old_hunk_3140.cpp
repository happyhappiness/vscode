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
