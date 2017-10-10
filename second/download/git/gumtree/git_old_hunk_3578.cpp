		return -1;

	return 0;
}

/**
 * Do the three-way merge using fake ancestor, their tree constructed
 * from the fake ancestor and the postimage of the patch, and our
 * state.
 */
static int run_fallback_merge_recursive(const struct am_state *state,
					unsigned char *orig_tree,
					unsigned char *our_tree,
					unsigned char *their_tree)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	int status;

	cp.git_cmd = 1;

	argv_array_pushf(&cp.env_array, "GITHEAD_%s=%.*s",
			 sha1_to_hex(their_tree), linelen(state->msg), state->msg);
	if (state->quiet)
		argv_array_push(&cp.env_array, "GIT_MERGE_VERBOSITY=0");

	argv_array_push(&cp.args, "merge-recursive");
	argv_array_push(&cp.args, sha1_to_hex(orig_tree));
	argv_array_push(&cp.args, "--");
	argv_array_push(&cp.args, sha1_to_hex(our_tree));
	argv_array_push(&cp.args, sha1_to_hex(their_tree));

	status = run_command(&cp) ? (-1) : 0;
	discard_cache();
	read_cache();
	return status;
}

/**
 * Attempt a threeway merge, using index_path as the temporary index.
 */
static int fall_back_threeway(const struct am_state *state, const char *index_path)
{
	unsigned char orig_tree[GIT_SHA1_RAWSZ], their_tree[GIT_SHA1_RAWSZ],
		      our_tree[GIT_SHA1_RAWSZ];

	if (get_sha1("HEAD", our_tree) < 0)
		hashcpy(our_tree, EMPTY_TREE_SHA1_BIN);

	if (build_fake_ancestor(state, index_path))
		return error("could not build fake ancestor");

	discard_cache();
	read_cache_from(index_path);

	if (write_index_as_tree(orig_tree, &the_index, index_path, 0, NULL))
		return error(_("Repository lacks necessary blobs to fall back on 3-way merge."));

	say(state, stdout, _("Using index info to reconstruct a base tree..."));

	if (!state->quiet) {
		/*
