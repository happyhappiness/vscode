static int apply_data(struct apply_state *state, struct patch *patch,
		      struct stat *st, const struct cache_entry *ce)
{
	struct image image;

	if (load_preimage(state, &image, patch, st, ce) < 0)
		return -1;

	if (patch->direct_to_threeway ||
	    apply_fragments(state, &image, patch) < 0) {
		/* Note: with --reject, apply_fragments() returns 0 */
		if (!state->threeway || try_threeway(state, &image, patch, st, ce) < 0)
			return -1;
	}
	patch->result = image.buf;
	patch->resultsize = image.len;
	add_to_fn_table(state, patch);
	free(image.line_allocated);

	if (0 < patch->is_delete && patch->resultsize)
		return error(_("removal patch leaves file contents"));

	return 0;
}