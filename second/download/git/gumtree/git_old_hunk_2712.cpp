		return -1;

	return 0;
}

/**
 * Attempt a threeway merge, using index_path as the temporary index.
 */
static int fall_back_threeway(const struct am_state *state, const char *index_path)
{
	unsigned char orig_tree[GIT_SHA1_RAWSZ], his_tree[GIT_SHA1_RAWSZ],
		      our_tree[GIT_SHA1_RAWSZ];
	const unsigned char *bases[1] = {orig_tree};
	struct merge_options o;
	struct commit *result;
	char *his_tree_name;

	if (get_sha1("HEAD", our_tree) < 0)
		hashcpy(our_tree, EMPTY_TREE_SHA1_BIN);

	if (build_fake_ancestor(state, index_path))
		return error("could not build fake ancestor");
