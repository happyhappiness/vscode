static struct ref_dir *get_loose_refs(struct ref_cache *refs)
{
	if (!refs->loose) {
		/*
		 * Mark the top-level directory complete because we
		 * are about to read the only subdirectory that can
		 * hold references:
		 */
		refs->loose = create_dir_entry(refs, "", 0, 0);
		/*
		 * Create an incomplete entry for "refs/":
		 */
		add_entry_to_dir(get_ref_dir(refs->loose),
				 create_dir_entry(refs, "refs/", 5, 1));
	}
	return get_ref_dir(refs->loose);
}