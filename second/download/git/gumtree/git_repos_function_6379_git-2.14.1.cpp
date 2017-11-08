static void validate_packed_ref_cache(struct files_ref_store *refs)
{
	if (refs->packed &&
	    !stat_validity_check(&refs->packed->validity,
				 files_packed_refs_path(refs)))
		clear_packed_ref_cache(refs);
}