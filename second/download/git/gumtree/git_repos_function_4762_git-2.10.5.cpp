static int apply_binary_fragment(struct apply_state *state,
				 struct image *img,
				 struct patch *patch)
{
	struct fragment *fragment = patch->fragments;
	unsigned long len;
	void *dst;

	if (!fragment)
		return error(_("missing binary patch data for '%s'"),
			     patch->new_name ?
			     patch->new_name :
			     patch->old_name);

	/* Binary patch is irreversible without the optional second hunk */
	if (state->apply_in_reverse) {
		if (!fragment->next)
			return error("cannot reverse-apply a binary patch "
				     "without the reverse hunk to '%s'",
				     patch->new_name
				     ? patch->new_name : patch->old_name);
		fragment = fragment->next;
	}
	switch (fragment->binary_patch_method) {
	case BINARY_DELTA_DEFLATED:
		dst = patch_delta(img->buf, img->len, fragment->patch,
				  fragment->size, &len);
		if (!dst)
			return -1;
		clear_image(img);
		img->buf = dst;
		img->len = len;
		return 0;
	case BINARY_LITERAL_DEFLATED:
		clear_image(img);
		img->len = fragment->size;
		img->buf = xmemdupz(fragment->patch, img->len);
		return 0;
	}
	return -1;
}