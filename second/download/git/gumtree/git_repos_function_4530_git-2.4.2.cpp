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