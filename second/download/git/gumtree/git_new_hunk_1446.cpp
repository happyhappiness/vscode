		if (!b)
			die("Not in a commit: %s", command_buf.buf);
		root = &b->branch_tree;
	} else {
		struct object_entry *e = parse_treeish_dataref(&p);
		root = new_tree_entry();
		oidcpy(&root->versions[1].oid, &e->idx.oid);
		if (!is_null_oid(&root->versions[1].oid))
			root->versions[1].mode = S_IFDIR;
		load_tree(root);
	}
	if (*p == '"') {
		static struct strbuf uq = STRBUF_INIT;
		const char *endp;
