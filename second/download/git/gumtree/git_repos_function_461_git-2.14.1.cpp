static struct commit *fake_working_tree_commit(struct diff_options *opt,
					       const char *path,
					       const char *contents_from)
{
	struct commit *commit;
	struct blame_origin *origin;
	struct commit_list **parent_tail, *parent;
	struct object_id head_oid;
	struct strbuf buf = STRBUF_INIT;
	const char *ident;
	time_t now;
	int size, len;
	struct cache_entry *ce;
	unsigned mode;
	struct strbuf msg = STRBUF_INIT;

	read_cache();
	time(&now);
	commit = alloc_commit_node();
	commit->object.parsed = 1;
	commit->date = now;
	parent_tail = &commit->parents;

	if (!resolve_ref_unsafe("HEAD", RESOLVE_REF_READING, head_oid.hash, NULL))
		die("no such ref: HEAD");

	parent_tail = append_parent(parent_tail, &head_oid);
	append_merge_parents(parent_tail);
	verify_working_tree_path(commit, path);

	origin = make_origin(commit, path);

	ident = fmt_ident("Not Committed Yet", "not.committed.yet", NULL, 0);
	strbuf_addstr(&msg, "tree 0000000000000000000000000000000000000000\n");
	for (parent = commit->parents; parent; parent = parent->next)
		strbuf_addf(&msg, "parent %s\n",
			    oid_to_hex(&parent->item->object.oid));
	strbuf_addf(&msg,
		    "author %s\n"
		    "committer %s\n\n"
		    "Version of %s from %s\n",
		    ident, ident, path,
		    (!contents_from ? path :
		     (!strcmp(contents_from, "-") ? "standard input" : contents_from)));
	set_commit_buffer_from_strbuf(commit, &msg);

	if (!contents_from || strcmp("-", contents_from)) {
		struct stat st;
		const char *read_from;
		char *buf_ptr;
		unsigned long buf_len;

		if (contents_from) {
			if (stat(contents_from, &st) < 0)
				die_errno("Cannot stat '%s'", contents_from);
			read_from = contents_from;
		}
		else {
			if (lstat(path, &st) < 0)
				die_errno("Cannot lstat '%s'", path);
			read_from = path;
		}
		mode = canon_mode(st.st_mode);

		switch (st.st_mode & S_IFMT) {
		case S_IFREG:
			if (DIFF_OPT_TST(opt, ALLOW_TEXTCONV) &&
			    textconv_object(read_from, mode, &null_oid, 0, &buf_ptr, &buf_len))
				strbuf_attach(&buf, buf_ptr, buf_len, buf_len + 1);
			else if (strbuf_read_file(&buf, read_from, st.st_size) != st.st_size)
				die_errno("cannot open or read '%s'", read_from);
			break;
		case S_IFLNK:
			if (strbuf_readlink(&buf, read_from, st.st_size) < 0)
				die_errno("cannot readlink '%s'", read_from);
			break;
		default:
			die("unsupported file type %s", read_from);
		}
	}
	else {
		/* Reading from stdin */
		mode = 0;
		if (strbuf_read(&buf, 0, 0) < 0)
			die_errno("failed to read from stdin");
	}
	convert_to_git(&the_index, path, buf.buf, buf.len, &buf, 0);
	origin->file.ptr = buf.buf;
	origin->file.size = buf.len;
	pretend_sha1_file(buf.buf, buf.len, OBJ_BLOB, origin->blob_oid.hash);

	/*
	 * Read the current index, replace the path entry with
	 * origin->blob_sha1 without mucking with its mode or type
	 * bits; we are not going to write this index out -- we just
	 * want to run "diff-index --cached".
	 */
	discard_cache();
	read_cache();

	len = strlen(path);
	if (!mode) {
		int pos = cache_name_pos(path, len);
		if (0 <= pos)
			mode = active_cache[pos]->ce_mode;
		else
			/* Let's not bother reading from HEAD tree */
			mode = S_IFREG | 0644;
	}
	size = cache_entry_size(len);
	ce = xcalloc(1, size);
	oidcpy(&ce->oid, &origin->blob_oid);
	memcpy(ce->name, path, len);
	ce->ce_flags = create_ce_flags(0);
	ce->ce_namelen = len;
	ce->ce_mode = create_ce_mode(mode);
	add_cache_entry(ce, ADD_CACHE_OK_TO_ADD|ADD_CACHE_OK_TO_REPLACE);

	cache_tree_invalidate_path(&the_index, path);

	return commit;
}