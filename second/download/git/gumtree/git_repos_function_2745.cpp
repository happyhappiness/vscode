static void clear_loose_ref_cache(struct ref_cache *refs)
{
	if (refs->loose) {
		free_ref_entry(refs->loose);
		refs->loose = NULL;
	}
}