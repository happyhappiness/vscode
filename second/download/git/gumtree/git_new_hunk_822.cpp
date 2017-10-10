	struct strbuf buf = STRBUF_INIT;
	struct strbuf bname = STRBUF_INIT;
	const char *ptr;
	char *found_ref;
	int len, early;

	strbuf_branchname(&bname, remote, 0);
	remote = bname.buf;

	memset(branch_head, 0, sizeof(branch_head));
	remote_head = get_merge_parent(remote);
	if (!remote_head)
		die(_("'%s' does not point to a commit"), remote);
