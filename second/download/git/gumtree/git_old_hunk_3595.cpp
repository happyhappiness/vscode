	free(preimage.line_allocated);
	free(postimage.line_allocated);

	return (applied_pos < 0);
}

static int apply_binary_fragment(struct image *img, struct patch *patch)
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
	if (apply_in_reverse) {
		if (!fragment->next)
			return error("cannot reverse-apply a binary patch "
				     "without the reverse hunk to '%s'",
				     patch->new_name
				     ? patch->new_name : patch->old_name);
		fragment = fragment->next;
