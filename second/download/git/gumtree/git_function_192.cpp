static int try_threeway(struct apply_state *state,
			struct image *image,
			struct patch *patch,
			struct stat *st,
			const struct cache_entry *ce)
{
	unsigned char pre_sha1[20], post_sha1[20], our_sha1[20];
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
		write_sha1_file("", 0, blob_type, pre_sha1);
	else if (get_sha1(patch->old_sha1_prefix, pre_sha1) ||
		 read_blob_object(&buf, pre_sha1, patch->old_mode))
		return error("repository lacks the necessary blob to fall back on 3-way merge.");

	fprintf(stderr, "Falling back to three-way merge...\n");

	img = strbuf_detach(&buf, &len);
	prepare_image(&tmp_image, img, len, 1);
	/* Apply the patch to get the post image */
	if (apply_fragments(state, &tmp_image, patch) < 0) {
		clear_image(&tmp_image);
		return -1;
	}
	/* post_sha1[] is theirs */
	write_sha1_file(tmp_image.buf, tmp_image.len, blob_type, post_sha1);
	clear_image(&tmp_image);

	/* our_sha1[] is ours */
	if (patch->is_new) {
		if (load_current(state, &tmp_image, patch))
			return error("cannot read the current contents of '%s'",
				     patch->new_name);
	} else {
		if (load_preimage(state, &tmp_image, patch, st, ce))
			return error("cannot read the current contents of '%s'",
				     patch->old_name);
	}
	write_sha1_file(tmp_image.buf, tmp_image.len, blob_type, our_sha1);
	clear_image(&tmp_image);

	/* in-core three-way merge between post and our using pre as base */
	status = three_way_merge(image, patch->new_name,
				 pre_sha1, our_sha1, post_sha1);
	if (status < 0) {
		fprintf(stderr, "Failed to fall back on three-way merge...\n");
		return status;
	}

	if (status) {
		patch->conflicted_threeway = 1;
		if (patch->is_new)
			oidclr(&patch->threeway_stage[0]);
		else
			hashcpy(patch->threeway_stage[0].hash, pre_sha1);
		hashcpy(patch->threeway_stage[1].hash, our_sha1);
		hashcpy(patch->threeway_stage[2].hash, post_sha1);
		fprintf(stderr, "Applied patch to '%s' with conflicts.\n", patch->new_name);
	} else {
		fprintf(stderr, "Applied patch to '%s' cleanly.\n", patch->new_name);
	}
	return 0;
}