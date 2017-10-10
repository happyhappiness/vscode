
	strbuf_reset(&path);
	strbuf_add(&path, state->base_dir, state->base_dir_len);
	strbuf_add(&path, ce->name, ce_namelen(ce));

	if (!check_path(path.buf, path.len, &st, state->base_dir_len)) {
		unsigned changed = ce_match_stat(ce, &st, CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE);
		if (!changed)
			return 0;
		if (!state->force) {
			if (!state->quiet)
				fprintf(stderr,
					"%s already exists, no checkout\n",
