static int fall_back_threeway(const struct am_state *state, const char *index_path)
{
	struct object_id orig_tree, their_tree, our_tree;
	const struct object_id *bases[1] = { &orig_tree };
	struct merge_options o;
	struct commit *result;
	char *their_tree_name;

	if (get_oid("HEAD", &our_tree) < 0)
		hashcpy(our_tree.hash, EMPTY_TREE_SHA1_BIN);

	if (build_fake_ancestor(state, index_path))
		return error("could not build fake ancestor");

	discard_cache();
	read_cache_from(index_path);

	if (write_index_as_tree(orig_tree.hash, &the_index, index_path, 0, NULL))
		return error(_("Repository lacks necessary blobs to fall back on 3-way merge."));

	say(state, stdout, _("Using index info to reconstruct a base tree..."));

	if (!state->quiet) {
		/*
		 * List paths that needed 3-way fallback, so that the user can
		 * review them with extra care to spot mismerges.
		 */
		struct rev_info rev_info;
		const char *diff_filter_str = "--diff-filter=AM";

		init_revisions(&rev_info, NULL);
		rev_info.diffopt.output_format = DIFF_FORMAT_NAME_STATUS;
		diff_opt_parse(&rev_info.diffopt, &diff_filter_str, 1, rev_info.prefix);
		add_pending_oid(&rev_info, "HEAD", &our_tree, 0);
		diff_setup_done(&rev_info.diffopt);
		run_diff_index(&rev_info, 1);
	}

	if (run_apply(state, index_path))
		return error(_("Did you hand edit your patch?\n"
				"It does not apply to blobs recorded in its index."));

	if (write_index_as_tree(their_tree.hash, &the_index, index_path, 0, NULL))
		return error("could not write tree");

	say(state, stdout, _("Falling back to patching base and 3-way merge..."));

	discard_cache();
	read_cache();

	/*
	 * This is not so wrong. Depending on which base we picked, orig_tree
	 * may be wildly different from ours, but their_tree has the same set of
	 * wildly different changes in parts the patch did not touch, so
	 * recursive ends up canceling them, saying that we reverted all those
	 * changes.
	 */

	init_merge_options(&o);

	o.branch1 = "HEAD";
	their_tree_name = xstrfmt("%.*s", linelen(state->msg), state->msg);
	o.branch2 = their_tree_name;

	if (state->quiet)
		o.verbosity = 0;

	if (merge_recursive_generic(&o, &our_tree, &their_tree, 1, bases, &result)) {
		rerere(state->allow_rerere_autoupdate);
		free(their_tree_name);
		return error(_("Failed to merge in the changes."));
	}

	free(their_tree_name);
	return 0;
}