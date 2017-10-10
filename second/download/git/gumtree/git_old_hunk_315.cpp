
/**
 * Resume the current am session by skipping the current patch.
 */
static void am_skip(struct am_state *state)
{
	unsigned char head[GIT_SHA1_RAWSZ];

	am_rerere_clear();

	if (get_sha1("HEAD", head))
		hashcpy(head, EMPTY_TREE_SHA1_BIN);

	if (clean_index(head, head))
		die(_("failed to clean index"));

	am_next(state);
	am_load(state);
	am_run(state, 0);
}
