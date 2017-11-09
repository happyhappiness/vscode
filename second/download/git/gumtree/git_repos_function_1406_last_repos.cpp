static int try_threeway(struct apply_state *state,
			struct image *image,
			struct patch *patch,
			struct stat *st,
			const struct cache_entry *ce)
{
	struct object_id pre_oid, post_oid, our_oid;
	struct strbuf buf = STRBUF_INIT;
	size_t len;
	int status;
	char *img;
	struct image tmp_image;

	/* No point falling back to 3-way merge in these cases */
	if (patch->is_delete ||
	    S_ISGITLINK(patch->old_mode) || S_ISGITLINK(patch->new_mode))
		return -1;

	/* Preimage the patch was prepared for */
	if (patch->is_new)
		write_sha1_file("", 0, blob_type, pre_oid.hash);
	else if (get_sha1(patch->old_sha1_prefix, pre_oid.hash) ||
		 read_blob_object(&buf, &pre_oid, patch->old_mode))
		return error(_("repository lacks the necessary blob to fall back on 3-way merge."));

	if (state->apply_verbosity > verbosity_silent)
		fprintf(stderr, _("Falling back to three-way merge...\n"));

	img = strbuf_detach(&buf, &len);
	prepare_image(&tmp_image, img, len, 1);
	/* Apply the patch to get the post image */
	if (apply_fragments(state, &tmp_image, patch) < 0) {
		clear_image(&tmp_image);
		return -1;
	}
	/* post_oid is theirs */
	write_sha1_file(tmp_image.buf, tmp_image.len, blob_type, post_oid.hash);
	clear_image(&tmp_image);

	/* our_oid is ours */
	if (patch->is_new) {
		if (load_current(state, &tmp_image, patch))
			return error(_("cannot read the current contents of '%s'"),
				     patch->new_name);
	} else {
		if (load_preimage(state, &tmp_image, patch, st, ce))
			return error(_("cannot read the current contents of '%s'"),
				     patch->old_name);
	}
	write_sha1_file(tmp_image.buf, tmp_image.len, blob_type, our_oid.hash);
	clear_image(&tmp_image);

	/* in-core three-way merge between post and our using pre as base */
	status = three_way_merge(image, patch->new_name,
				 &pre_oid, &our_oid, &post_oid);
	if (status < 0) {
		if (state->apply_verbosity > verbosity_silent)
			fprintf(stderr,
				_("Failed to fall back on three-way merge...\n"));
		return status;
	}

	if (status) {
		patch->conflicted_threeway = 1;
		if (patch->is_new)
			oidclr(&patch->threeway_stage[0]);
		else
			oidcpy(&patch->threeway_stage[0], &pre_oid);
		oidcpy(&patch->threeway_stage[1], &our_oid);
		oidcpy(&patch->threeway_stage[2], &post_oid);
		if (state->apply_verbosity > verbosity_silent)
			fprintf(stderr,
				_("Applied patch to '%s' with conflicts.\n"),
				patch->new_name);
	} else {
		if (state->apply_verbosity > verbosity_silent)
			fprintf(stderr,
				_("Applied patch to '%s' cleanly.\n"),
				patch->new_name);
	}
	return 0;
}