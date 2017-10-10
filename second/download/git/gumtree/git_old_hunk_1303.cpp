			       i + 1);
			write_name(path);
		}
	}
}

static int ce_excluded(struct dir_struct *dir, const struct cache_entry *ce)
{
	int dtype = ce_to_dtype(ce);
	return is_excluded(dir, ce->name, &dtype);
}

static void show_files(struct dir_struct *dir)
{
	int i;

	/* For cached/deleted files we don't need to even do the readdir */
	if (show_others || show_killed) {
		if (!show_others)
			dir->flags |= DIR_COLLECT_KILLED_ONLY;
		fill_directory(dir, &pathspec);
		if (show_others)
			show_other_files(dir);
		if (show_killed)
			show_killed_files(dir);
	}
	if (show_cached || show_stage) {
		for (i = 0; i < active_nr; i++) {
			const struct cache_entry *ce = active_cache[i];
			if ((dir->flags & DIR_SHOW_IGNORED) &&
			    !ce_excluded(dir, ce))
				continue;
			if (show_unmerged && !ce_stage(ce))
				continue;
			if (ce->ce_flags & CE_UPDATE)
				continue;
			show_ce_entry(ce_stage(ce) ? tag_unmerged :
				(ce_skip_worktree(ce) ? tag_skip_worktree : tag_cached), ce);
		}
	}
	if (show_deleted || show_modified) {
		for (i = 0; i < active_nr; i++) {
			const struct cache_entry *ce = active_cache[i];
			struct stat st;
			int err;
			if ((dir->flags & DIR_SHOW_IGNORED) &&
			    !ce_excluded(dir, ce))
				continue;
			if (ce->ce_flags & CE_UPDATE)
				continue;
			if (ce_skip_worktree(ce))
				continue;
			err = lstat(ce->name, &st);
			if (show_deleted && err)
				show_ce_entry(tag_removed, ce);
			if (show_modified && ce_modified(ce, &st, 0))
				show_ce_entry(tag_modified, ce);
		}
	}
}

/*
 * Prune the index to only contain stuff starting with "prefix"
 */
static void prune_cache(const char *prefix, size_t prefixlen)
{
	int pos;
	unsigned int first, last;

	if (!prefix)
		return;
	pos = cache_name_pos(prefix, prefixlen);
	if (pos < 0)
		pos = -pos-1;
	first = pos;
	last = active_nr;
	while (last > first) {
		int next = (last + first) >> 1;
		const struct cache_entry *ce = active_cache[next];
		if (!strncmp(ce->name, prefix, prefixlen)) {
			first = next+1;
			continue;
		}
		last = next;
	}
	memmove(active_cache, active_cache + pos,
		(last - pos) * sizeof(struct cache_entry *));
	active_nr = last - pos;
}

/*
 * Read the tree specified with --with-tree option
 * (typically, HEAD) into stage #1 and then
 * squash them down to stage #0.  This is used for
 * --error-unmatch to list and check the path patterns
 * that were given from the command line.  We are not
 * going to write this index out.
 */
void overlay_tree_on_cache(const char *tree_name, const char *prefix)
{
	struct tree *tree;
	unsigned char sha1[20];
	struct pathspec pathspec;
	struct cache_entry *last_stage0 = NULL;
	int i;

	if (get_sha1(tree_name, sha1))
		die("tree-ish %s not found.", tree_name);
	tree = parse_tree_indirect(sha1);
	if (!tree)
		die("bad tree-ish %s", tree_name);

	/* Hoist the unmerged entries up to stage #3 to make room */
	for (i = 0; i < active_nr; i++) {
		struct cache_entry *ce = active_cache[i];
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
	if (read_tree(tree, 1, &pathspec))
		die("unable to read tree entries %s", tree_name);

	for (i = 0; i < active_nr; i++) {
		struct cache_entry *ce = active_cache[i];
		switch (ce_stage(ce)) {
		case 0:
			last_stage0 = ce;
			/* fallthru */
		default:
			continue;
