static int apply_binary(struct apply_state *state,
			struct image *img,
			struct patch *patch)
{
	const char *name = patch->old_name ? patch->old_name : patch->new_name;
	struct object_id oid;

	/*
	 * For safety, we require patch index line to contain
	 * full 40-byte textual SHA1 for old and new, at least for now.
	 */
	if (strlen(patch->old_sha1_prefix) != 40 ||
	    strlen(patch->new_sha1_prefix) != 40 ||
	    get_oid_hex(patch->old_sha1_prefix, &oid) ||
	    get_oid_hex(patch->new_sha1_prefix, &oid))
		return error(_("cannot apply binary patch to '%s' "
			       "without full index line"), name);

	if (patch->old_name) {
		/*
		 * See if the old one matches what the patch
		 * applies to.
		 */
		hash_sha1_file(img->buf, img->len, blob_type, oid.hash);
		if (strcmp(oid_to_hex(&oid), patch->old_sha1_prefix))
			return error(_("the patch applies to '%s' (%s), "
				       "which does not match the "
				       "current contents."),
				     name, oid_to_hex(&oid));
	}
	else {
		/* Otherwise, the old one must be empty. */
		if (img->len)
			return error(_("the patch applies to an empty "
				       "'%s' but it is not empty"), name);
	}

	get_oid_hex(patch->new_sha1_prefix, &oid);
	if (is_null_oid(&oid)) {
		clear_image(img);
		return 0; /* deletion patch */
	}

	if (has_sha1_file(oid.hash)) {
		/* We already have the postimage */
		enum object_type type;
		unsigned long size;
		char *result;

		result = read_sha1_file(oid.hash, &type, &size);
		if (!result)
			return error(_("the necessary postimage %s for "
				       "'%s' cannot be read"),
				     patch->new_sha1_prefix, name);
		clear_image(img);
		img->buf = result;
		img->len = size;
	} else {
		/*
		 * We have verified buf matches the preimage;
		 * apply the patch data to it, which is stored
		 * in the patch->fragments->{patch,size}.
		 */
		if (apply_binary_fragment(state, img, patch))
			return error(_("binary patch does not apply to '%s'"),
				     name);

		/* verify that the result matches */
		hash_sha1_file(img->buf, img->len, blob_type, oid.hash);
		if (strcmp(oid_to_hex(&oid), patch->new_sha1_prefix))
			return error(_("binary patch to '%s' creates incorrect result (expecting %s, got %s)"),
				name, patch->new_sha1_prefix, oid_to_hex(&oid));
	}

	return 0;
}