static void clear_loose_ref_cache(struct files_ref_store *refs)
{
	if (refs->loose) {
		free_ref_cache(refs->loose);
		refs->loose = NULL;
	}
}