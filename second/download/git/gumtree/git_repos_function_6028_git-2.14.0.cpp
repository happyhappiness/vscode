static void update_one(const char *path)
{
	if (!verify_path(path)) {
		fprintf(stderr, "Ignoring path %s\n", path);
		return;
	}
	if (mark_valid_only) {
		if (mark_ce_flags(path, CE_VALID, mark_valid_only == MARK_FLAG))
			die("Unable to mark file %s", path);
		return;
	}
	if (mark_skip_worktree_only) {
		if (mark_ce_flags(path, CE_SKIP_WORKTREE, mark_skip_worktree_only == MARK_FLAG))
			die("Unable to mark file %s", path);
		return;
	}

	if (force_remove) {
		if (remove_file_from_cache(path))
			die("git update-index: unable to remove %s", path);
		report("remove '%s'", path);
		return;
	}
	if (process_path(path))
		die("Unable to process path %s", path);
	report("add '%s'", path);
}