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

/**
 * Commits the current index with state->msg as the commit message and
 * state->author_name, state->author_email and state->author_date as the author
