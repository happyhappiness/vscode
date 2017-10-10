 *
 * Will always return 0 as the patch should never be skipped.
 */
static int parse_mail_rebase(struct am_state *state, const char *mail)
{
	struct commit *commit;
	unsigned char commit_sha1[GIT_SHA1_RAWSZ];

	if (get_mail_commit_sha1(commit_sha1, mail) < 0)
		die(_("could not parse %s"), mail);

	commit = lookup_commit_or_die(commit_sha1, mail);

	get_commit_info(state, commit);

	write_commit_patch(state, commit);

	hashcpy(state->orig_commit, commit_sha1);
	write_state_text(state, "original-commit", sha1_to_hex(commit_sha1));

	return 0;
}

/**
 * Applies current patch with git-apply. Returns 0 on success, -1 otherwise. If
 * `index_file` is not NULL, the patch will be applied to that index.
 */
static int run_apply(const struct am_state *state, const char *index_file)
{
	struct child_process cp = CHILD_PROCESS_INIT;

	cp.git_cmd = 1;

	if (index_file)
		argv_array_pushf(&cp.env_array, "GIT_INDEX_FILE=%s", index_file);

	/*
	 * If we are allowed to fall back on 3-way merge, don't give false
	 * errors during the initial attempt.
	 */
	if (state->threeway && !index_file) {
		cp.no_stdout = 1;
		cp.no_stderr = 1;
	}

	argv_array_push(&cp.args, "apply");

	argv_array_pushv(&cp.args, state->git_apply_opts.argv);

	if (index_file)
		argv_array_push(&cp.args, "--cached");
	else
		argv_array_push(&cp.args, "--index");

	argv_array_push(&cp.args, am_path(state, "patch"));

	if (run_command(&cp))
		return -1;

	/* Reload index as git-apply will have modified it. */
	discard_cache();
	read_cache_from(index_file ? index_file : get_index_file());

	return 0;
}

/**
 * Builds an index that contains just the blobs needed for a 3way merge.
