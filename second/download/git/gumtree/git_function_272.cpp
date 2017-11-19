static int apply_fragments(struct apply_state *state, struct image *img, struct patch *patch)
{
	struct fragment *frag = patch->fragments;
	const char *name = patch->old_name ? patch->old_name : patch->new_name;
	unsigned ws_rule = patch->ws_rule;
	unsigned inaccurate_eof = patch->inaccurate_eof;
	int nth = 0;

	if (patch->is_binary)
		return apply_binary(state, img, patch);

	while (frag) {
		nth++;
		if (apply_one_fragment(state, img, frag, inaccurate_eof, ws_rule, nth)) {
			error(_("patch failed: %s:%ld"), name, frag->oldpos);
			if (!state->apply_with_reject)
				return -1;
			frag->rejected = 1;
		}
		frag = frag->next;
	}
	return 0;
}