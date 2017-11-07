static int load_preimage(struct apply_state *state,
			 struct image *image,
			 struct patch *patch, struct stat *st,
			 const struct cache_entry *ce)
{
	struct strbuf buf = STRBUF_INIT;
	size_t len;
	char *img;
	struct patch *previous;
	int status;

	previous = previous_patch(state, patch, &status);
	if (status)
		return error(_("path %s has been renamed/deleted"),
			     patch->old_name);
	if (previous) {
		/* We have a patched copy in memory; use that. */
		strbuf_add(&buf, previous->result, previous->resultsize);
	} else {
		status = load_patch_target(state, &buf, ce, st,
					   patch->old_name, patch->old_mode);
		if (status < 0)
			return status;
		else if (status == SUBMODULE_PATCH_WITHOUT_INDEX) {
			/*
			 * There is no way to apply subproject
			 * patch without looking at the index.
			 * NEEDSWORK: shouldn't this be flagged
			 * as an error???
			 */
			free_fragment_list(patch->fragments);
			patch->fragments = NULL;
		} else if (status) {
			return error(_("failed to read %s"), patch->old_name);
		}
	}

	img = strbuf_detach(&buf, &len);
	prepare_image(image, img, len, !patch->is_binary);
	return 0;
}