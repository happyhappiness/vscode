	 * getting updated.
	 */
	lock = lock_any_ref_for_update(ref, sha1, 0, NULL);
	if (!lock)
		return error("cannot lock ref '%s'", ref);
	log_file = git_pathdup("logs/%s", ref);
	if (!file_exists(log_file))
		goto finish;
	if (!cmd->dry_run) {
		newlog_path = git_pathdup("logs/%s.lock", ref);
		cb.newlog = fopen(newlog_path, "w");
	}

