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