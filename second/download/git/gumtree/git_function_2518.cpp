static void clear_packed_ref_cache(struct ref_cache *refs)
{
	if (refs->packed) {
		struct packed_ref_cache *packed_refs = refs->packed;

		if (packed_refs->lock)
			die("internal error: packed-ref cache cleared while locked");
		refs->packed = NULL;
		release_packed_ref_cache(packed_refs);
	}
}