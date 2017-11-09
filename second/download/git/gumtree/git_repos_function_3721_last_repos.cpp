void gitmodules_config(void)
{
	const char *work_tree = get_git_work_tree();
	if (work_tree) {
		struct strbuf gitmodules_path = STRBUF_INIT;
		int pos;
		strbuf_addstr(&gitmodules_path, work_tree);
		strbuf_addstr(&gitmodules_path, "/.gitmodules");
		if (read_cache() < 0)
			die("index file corrupt");
		pos = cache_name_pos(".gitmodules", 11);
		if (pos < 0) { /* .gitmodules not found or isn't merged */
			pos = -1 - pos;
			if (active_nr > pos) {  /* there is a .gitmodules */
				const struct cache_entry *ce = active_cache[pos];
				if (ce_namelen(ce) == 11 &&
				    !memcmp(ce->name, ".gitmodules", 11))
					gitmodules_is_unmerged = 1;
			}
		} else if (pos < active_nr) {
			struct stat st;
			if (lstat(".gitmodules", &st) == 0 &&
			    ce_match_stat(active_cache[pos], &st, 0) & DATA_CHANGED)
				gitmodules_is_modified = 1;
		}

		if (!gitmodules_is_unmerged)
			git_config_from_file(git_modules_config,
				gitmodules_path.buf, NULL);
		strbuf_release(&gitmodules_path);
	}
}