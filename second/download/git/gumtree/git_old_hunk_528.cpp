
	if (!active_cache_tree)
		active_cache_tree = cache_tree();

	if (!cache_tree_fully_valid(active_cache_tree))
		if (cache_tree_update(&the_index, 0))
			return error(_("Unable to update cache tree\n"));

	return !hashcmp(active_cache_tree->sha1, head_commit->tree->object.oid.hash);
}

/*
 * If we are cherry-pick, and if the merge did not result in
 * hand-editing, we will hit this commit and inherit the original
 * author date and name.
 * If we are revert, or if our cherry-pick results in a hand merge,
 * we had better say that the current user is responsible for that.
 */
static int run_git_commit(const char *defmsg, struct replay_opts *opts,
			  int allow_empty)
{
	struct argv_array array;
	int rc;
	const char *value;

	argv_array_init(&array);
	argv_array_push(&array, "commit");
	argv_array_push(&array, "-n");

	if (opts->gpg_sign)
		argv_array_pushf(&array, "-S%s", opts->gpg_sign);
	if (opts->signoff)
		argv_array_push(&array, "-s");
	if (!opts->edit) {
		argv_array_push(&array, "-F");
		argv_array_push(&array, defmsg);
		if (!opts->signoff &&
		    !opts->record_origin &&
		    git_config_get_value("commit.cleanup", &value))
			argv_array_push(&array, "--cleanup=verbatim");
	}

	if (allow_empty)
		argv_array_push(&array, "--allow-empty");

	if (opts->allow_empty_message)
		argv_array_push(&array, "--allow-empty-message");

	rc = run_command_v_opt(array.argv, RUN_GIT_CMD);
	argv_array_clear(&array);
	return rc;
}

static int is_original_commit_empty(struct commit *commit)
{
	const unsigned char *ptree_sha1;

	if (parse_commit(commit))
		return error(_("Could not parse commit %s\n"),
			     oid_to_hex(&commit->object.oid));
	if (commit->parents) {
		struct commit *parent = commit->parents->item;
		if (parse_commit(parent))
			return error(_("Could not parse parent commit %s\n"),
				oid_to_hex(&parent->object.oid));
		ptree_sha1 = parent->tree->object.oid.hash;
	} else {
		ptree_sha1 = EMPTY_TREE_SHA1_BIN; /* commit is root */
	}

