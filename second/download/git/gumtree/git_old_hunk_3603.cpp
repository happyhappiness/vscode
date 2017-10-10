	} else {
		fprintf(stderr, "Applied patch to '%s' cleanly.\n", patch->new_name);
	}
	return 0;
}

static int apply_data(struct patch *patch, struct stat *st, const struct cache_entry *ce)
{
	struct image image;

	if (load_preimage(&image, patch, st, ce) < 0)
		return -1;

	if (patch->direct_to_threeway ||
	    apply_fragments(&image, patch) < 0) {
		/* Note: with --reject, apply_fragments() returns 0 */
		if (!threeway || try_threeway(&image, patch, st, ce) < 0)
			return -1;
	}
	patch->result = image.buf;
	patch->resultsize = image.len;
	add_to_fn_table(patch);
	free(image.line_allocated);

	if (0 < patch->is_delete && patch->resultsize)
		return error(_("removal patch leaves file contents"));

	return 0;
