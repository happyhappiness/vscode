
	fprintf(stderr, "Falling back to three-way merge...\n");

	img = strbuf_detach(&buf, &len);
	prepare_image(&tmp_image, img, len, 1);
	/* Apply the patch to get the post image */
	if (apply_fragments(&tmp_image, patch) < 0) {
		clear_image(&tmp_image);
		return -1;
	}
	/* post_sha1[] is theirs */
	write_sha1_file(tmp_image.buf, tmp_image.len, blob_type, post_sha1);
	clear_image(&tmp_image);

	/* our_sha1[] is ours */
	if (patch->is_new) {
		if (load_current(&tmp_image, patch))
			return error("cannot read the current contents of '%s'",
				     patch->new_name);
	} else {
		if (load_preimage(&tmp_image, patch, st, ce))
			return error("cannot read the current contents of '%s'",
				     patch->old_name);
	}
	write_sha1_file(tmp_image.buf, tmp_image.len, blob_type, our_sha1);
	clear_image(&tmp_image);

