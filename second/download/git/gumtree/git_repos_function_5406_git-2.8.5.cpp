static int do_reupdate(int ac, const char **av,
		       const char *prefix, int prefix_length)
{
	/* Read HEAD and run update-index on paths that are
	 * merged and already different between index and HEAD.
	 */
	int pos;
	int has_head = 1;
	struct pathspec pathspec;

	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_CWD,
		       prefix, av + 1);

	if (read_ref("HEAD", head_sha1))
		/* If there is no HEAD, that means it is an initial
		 * commit.  Update everything in the index.
		 */
		has_head = 0;
 redo:
	for (pos = 0; pos < active_nr; pos++) {
		const struct cache_entry *ce = active_cache[pos];
		struct cache_entry *old = NULL;
		int save_nr;
		char *path;

		if (ce_stage(ce) || !ce_path_match(ce, &pathspec, NULL))
			continue;
		if (has_head)
			old = read_one_ent(NULL, head_sha1,
					   ce->name, ce_namelen(ce), 0);
		if (old && ce->ce_mode == old->ce_mode &&
		    !hashcmp(ce->sha1, old->sha1)) {
			free(old);
			continue; /* unchanged */
		}
		/* Be careful.  The working tree may not have the
		 * path anymore, in which case, under 'allow_remove',
		 * or worse yet 'allow_replace', active_nr may decrease.
		 */
		save_nr = active_nr;
		path = xstrdup(ce->name);
		update_one(path);
		free(path);
		free(old);
		if (save_nr != active_nr)
			goto redo;
	}
	free_pathspec(&pathspec);
	return 0;
}