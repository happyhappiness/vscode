			       i + 1);
			write_name(path);
		}
	}
}

static int ce_excluded(struct dir_struct *dir, struct index_state *istate,
		       const char *fullname, const struct cache_entry *ce)
{
	int dtype = ce_to_dtype(ce);
	return is_excluded(dir, istate, fullname, &dtype);
}

static void construct_fullname(struct strbuf *out, const struct repository *repo,
			       const struct cache_entry *ce)
{
	strbuf_reset(out);
	if (repo->submodule_prefix)
		strbuf_addstr(out, repo->submodule_prefix);
	strbuf_addstr(out, ce->name);
}

static void show_files(struct repository *repo, struct dir_struct *dir)
{
	int i;
	struct strbuf fullname = STRBUF_INIT;

	/* For cached/deleted files we don't need to even do the readdir */
	if (show_others || show_killed) {
		if (!show_others)
			dir->flags |= DIR_COLLECT_KILLED_ONLY;
		fill_directory(dir, repo->index, &pathspec);
		if (show_others)
			show_other_files(repo->index, dir);
		if (show_killed)
			show_killed_files(repo->index, dir);
	}
	if (show_cached || show_stage) {
		for (i = 0; i < repo->index->cache_nr; i++) {
			const struct cache_entry *ce = repo->index->cache[i];

			construct_fullname(&fullname, repo, ce);

			if ((dir->flags & DIR_SHOW_IGNORED) &&
			    !ce_excluded(dir, repo->index, fullname.buf, ce))
				continue;
			if (show_unmerged && !ce_stage(ce))
				continue;
			if (ce->ce_flags & CE_UPDATE)
				continue;
			show_ce(repo, dir, ce, fullname.buf,
				ce_stage(ce) ? tag_unmerged :
				(ce_skip_worktree(ce) ? tag_skip_worktree :
				 tag_cached));
		}
	}
	if (show_deleted || show_modified) {
		for (i = 0; i < repo->index->cache_nr; i++) {
			const struct cache_entry *ce = repo->index->cache[i];
			struct stat st;
			int err;

			construct_fullname(&fullname, repo, ce);

			if ((dir->flags & DIR_SHOW_IGNORED) &&
			    !ce_excluded(dir, repo->index, fullname.buf, ce))
				continue;
			if (ce->ce_flags & CE_UPDATE)
				continue;
			if (ce_skip_worktree(ce))
				continue;
			err = lstat(fullname.buf, &st);
			if (show_deleted && err)
				show_ce(repo, dir, ce, fullname.buf, tag_removed);
			if (show_modified && ie_modified(repo->index, ce, &st, 0))
				show_ce(repo, dir, ce, fullname.buf, tag_modified);
		}
	}

	strbuf_release(&fullname);
}

/*
 * Prune the index to only contain stuff starting with "prefix"
 */
static void prune_index(struct index_state *istate,
			const char *prefix, size_t prefixlen)
{
	int pos;
	unsigned int first, last;

	if (!prefix)
		return;
	pos = index_name_pos(istate, prefix, prefixlen);
	if (pos < 0)
		pos = -pos-1;
	first = pos;
	last = istate->cache_nr;
	while (last > first) {
		int next = (last + first) >> 1;
		const struct cache_entry *ce = istate->cache[next];
		if (!strncmp(ce->name, prefix, prefixlen)) {
			first = next+1;
			continue;
		}
		last = next;
	}
	memmove(istate->cache, istate->cache + pos,
		(last - pos) * sizeof(struct cache_entry *));
	istate->cache_nr = last - pos;
}

static int get_common_prefix_len(const char *common_prefix)
{
	int common_prefix_len;

	if (!common_prefix)
		return 0;

	common_prefix_len = strlen(common_prefix);

	/*
	 * If the prefix has a trailing slash, strip it so that submodules wont
	 * be pruned from the index.
	 */
	if (common_prefix[common_prefix_len - 1] == '/')
		common_prefix_len--;

	return common_prefix_len;
}

/*
 * Read the tree specified with --with-tree option
 * (typically, HEAD) into stage #1 and then
 * squash them down to stage #0.  This is used for
 * --error-unmatch to list and check the path patterns
 * that were given from the command line.  We are not
 * going to write this index out.
 */
void overlay_tree_on_index(struct index_state *istate,
			   const char *tree_name, const char *prefix)
{
	struct tree *tree;
	struct object_id oid;
	struct pathspec pathspec;
	struct cache_entry *last_stage0 = NULL;
	int i;

	if (get_oid(tree_name, &oid))
		die("tree-ish %s not found.", tree_name);
	tree = parse_tree_indirect(&oid);
	if (!tree)
		die("bad tree-ish %s", tree_name);

	/* Hoist the unmerged entries up to stage #3 to make room */
	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce = istate->cache[i];
		if (!ce_stage(ce))
			continue;
		ce->ce_flags |= CE_STAGEMASK;
	}

	if (prefix) {
		static const char *(matchbuf[1]);
		matchbuf[0] = NULL;
		parse_pathspec(&pathspec, PATHSPEC_ALL_MAGIC,
			       PATHSPEC_PREFER_CWD, prefix, matchbuf);
	} else
		memset(&pathspec, 0, sizeof(pathspec));
	if (read_tree(tree, 1, &pathspec, istate))
		die("unable to read tree entries %s", tree_name);

	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce = istate->cache[i];
		switch (ce_stage(ce)) {
		case 0:
			last_stage0 = ce;
			/* fallthru */
		default:
			continue;
