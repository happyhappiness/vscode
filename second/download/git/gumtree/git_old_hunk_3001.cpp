	hold_locked_index(&index_lock, 1);

	for (i = 0; i < update->nr; i++) {
		struct string_list_item *item = &update->items[i];
		if (add_file_to_cache(item->string, 0))
			exit(128);
	}

	if (active_cache_changed) {
		if (write_locked_index(&the_index, &index_lock, COMMIT_LOCK))
			die("Unable to write new index file");
	} else
		rollback_lock_file(&index_lock);
}

static int do_plain_rerere(struct string_list *rr, int fd)
{
	struct string_list conflict = STRING_LIST_INIT_DUP;
	struct string_list update = STRING_LIST_INIT_DUP;
	int i;

	find_conflict(&conflict);

	/*
	 * MERGE_RR records paths with conflicts immediately after merge
	 * failed.  Some of the conflicted paths might have been hand resolved
	 * in the working tree since then, but the initial run would catch all
	 * and register their preimages.
	 */

	for (i = 0; i < conflict.nr; i++) {
		const char *path = conflict.items[i].string;
		if (!string_list_has_string(rr, path)) {
			unsigned char sha1[20];
			char *hex;
			int ret;
			ret = handle_file(path, sha1, NULL);
			if (ret < 1)
				continue;
			hex = xstrdup(sha1_to_hex(sha1));
			string_list_insert(rr, path)->util = hex;
			if (mkdir_in_gitdir(git_path("rr-cache/%s", hex)))
				continue;
			handle_file(path, NULL, rerere_path(hex, "preimage"));
			fprintf(stderr, "Recorded preimage for '%s'\n", path);
		}
	}

	/*
	 * Now some of the paths that had conflicts earlier might have been
	 * hand resolved.  Others may be similar to a conflict already that
	 * was resolved before.
	 */

	for (i = 0; i < rr->nr; i++) {
		int ret;
		const char *path = rr->items[i].string;
		const char *name = (const char *)rr->items[i].util;

		if (has_rerere_resolution(name)) {
			if (!merge(name, path)) {
				const char *msg;
				if (rerere_autoupdate) {
					string_list_insert(&update, path);
					msg = "Staged '%s' using previous resolution.\n";
				} else
					msg = "Resolved '%s' using previous resolution.\n";
				fprintf(stderr, msg, path);
				goto mark_resolved;
			}
		}

		/* Let's see if we have resolved it. */
		ret = handle_file(path, NULL, NULL);
		if (ret)
			continue;

		fprintf(stderr, "Recorded resolution for '%s'.\n", path);
		copy_file(rerere_path(name, "postimage"), path, 0666);
	mark_resolved:
		rr->items[i].util = NULL;
	}

	if (update.nr)
		update_paths(&update);

	return write_rr(rr, fd);
}

