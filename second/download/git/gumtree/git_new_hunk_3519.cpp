	 * any file at all, we'll go ahead and commit to it all:
	 * by then we've already committed ourselves and can't fail
	 * in the middle)
	 */
	if (!index_only) {
		int removed = 0, gitmodules_modified = 0;
		struct strbuf buf = STRBUF_INIT;
		for (i = 0; i < list.nr; i++) {
			const char *path = list.entry[i].name;
			if (list.entry[i].is_submodule) {
				if (is_empty_dir(path)) {
					if (!rmdir(path)) {
						removed = 1;
						if (!remove_path_from_gitmodules(path))
							gitmodules_modified = 1;
						continue;
					}
				} else {
					strbuf_reset(&buf);
					strbuf_addstr(&buf, path);
					if (!remove_dir_recursively(&buf, 0)) {
						removed = 1;
						if (!remove_path_from_gitmodules(path))
							gitmodules_modified = 1;
						strbuf_release(&buf);
						continue;
					} else if (!file_exists(path))
						/* Submodule was removed by user */
						if (!remove_path_from_gitmodules(path))
							gitmodules_modified = 1;
					/* Fallthrough and let remove_path() fail. */
				}
			}
			if (!remove_path(path)) {
				removed = 1;
				continue;
			}
			if (!removed)
				die_errno("git rm: '%s'", path);
		}
		strbuf_release(&buf);
		if (gitmodules_modified)
			stage_updated_gitmodules();
	}

	if (active_cache_changed) {
		if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
