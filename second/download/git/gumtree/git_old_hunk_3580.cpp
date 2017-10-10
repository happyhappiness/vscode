	 * may be wildly different from ours, but their_tree has the same set of
	 * wildly different changes in parts the patch did not touch, so
	 * recursive ends up canceling them, saying that we reverted all those
	 * changes.
	 */

	if (run_fallback_merge_recursive(state, orig_tree, our_tree, their_tree)) {
		rerere(state->allow_rerere_autoupdate);
		return error(_("Failed to merge in the changes."));
	}

	return 0;
}

/**
 * Commits the current index with state->msg as the commit message and
 * state->author_name, state->author_email and state->author_date as the author
