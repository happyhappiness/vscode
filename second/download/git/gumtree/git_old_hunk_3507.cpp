	}

	if (run_apply(state, index_path))
		return error(_("Did you hand edit your patch?\n"
				"It does not apply to blobs recorded in its index."));

	if (write_index_as_tree(his_tree, &the_index, index_path, 0, NULL))
		return error("could not write tree");

	say(state, stdout, _("Falling back to patching base and 3-way merge..."));

	discard_cache();
	read_cache();

	/*
	 * This is not so wrong. Depending on which base we picked, orig_tree
	 * may be wildly different from ours, but his_tree has the same set of
	 * wildly different changes in parts the patch did not touch, so
	 * recursive ends up canceling them, saying that we reverted all those
	 * changes.
	 */

	if (run_fallback_merge_recursive(state, orig_tree, our_tree, his_tree)) {
		rerere(state->allow_rerere_autoupdate);
		return error(_("Failed to merge in the changes."));
	}

	return 0;
}
