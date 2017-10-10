		return -1;

	return 0;
}

/**
 * Attempt a threeway merge, using index_path as the temporary index.
 */
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
