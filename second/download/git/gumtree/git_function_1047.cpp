int checkout_entry(struct cache_entry *ce,
		   const struct checkout *state, char *topath)
{
	static struct strbuf path = STRBUF_INIT;
	struct stat st;

	if (topath)
		return write_entry(ce, topath, state, 1);

	strbuf_reset(&path);
	strbuf_add(&path, state->base_dir, state->base_dir_len);
	strbuf_add(&path, ce->name, ce_namelen(ce));

	if (!check_path(path.buf, path.len, &st, state->base_dir_len)) {
		const struct submodule *sub;
		unsigned changed = ce_match_stat(ce, &st, CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE);
		/*
		 * Needs to be checked before !changed returns early,
		 * as the possibly empty directory was not changed
		 */
		sub = submodule_from_ce(ce);
		if (sub) {
			int err;
			if (!is_submodule_populated_gently(ce->name, &err)) {
				struct stat sb;
				if (lstat(ce->name, &sb))
					die(_("could not stat file '%s'"), ce->name);
				if (!(st.st_mode & S_IFDIR))
					unlink_or_warn(ce->name);

				return submodule_move_head(ce->name,
					NULL, oid_to_hex(&ce->oid),
					SUBMODULE_MOVE_HEAD_FORCE);
			} else
				return submodule_move_head(ce->name,
					"HEAD", oid_to_hex(&ce->oid),
					SUBMODULE_MOVE_HEAD_FORCE);
		}

		if (!changed)
			return 0;
		if (!state->force) {
			if (!state->quiet)
				fprintf(stderr,
					"%s already exists, no checkout\n",
					path.buf);
			return -1;
		}

		/*
		 * We unlink the old file, to get the new one with the
		 * right permissions (including umask, which is nasty
		 * to emulate by hand - much easier to let the system
		 * just do the right thing)
		 */
		if (S_ISDIR(st.st_mode)) {
			/* If it is a gitlink, leave it alone! */
			if (S_ISGITLINK(ce->ce_mode))
				return 0;
			if (!state->force)
				return error("%s is a directory", path.buf);
			remove_subtree(&path);
		} else if (unlink(path.buf))
			return error_errno("unable to unlink old '%s'", path.buf);
	} else if (state->not_new)
		return 0;

	create_directories(path.buf, path.len, state);
	return write_entry(ce, path.buf, state, 0);
}