static struct ref_cache *get_loose_ref_cache(struct files_ref_store *refs)
{
	if (!refs->loose) {
		/*
		 * Mark the top-level directory complete because we
		 * are about to read the only subdirectory that can
		 * hold references:
		 */
		refs->loose = create_ref_cache(&refs->base, loose_fill_ref_dir);

		/* We're going to fill the top level ourselves: */
		refs->loose->root->flag &= ~REF_INCOMPLETE;

		/*
		 * Add an incomplete entry for "refs/" (to be filled
		 * lazily):
		 */
		add_entry_to_dir(get_ref_dir(refs->loose->root),
				 create_dir_entry(refs->loose, "refs/", 5, 1));
	}
	return refs->loose;
}