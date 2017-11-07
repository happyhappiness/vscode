static void add_packed_ref(struct files_ref_store *refs,
			   const char *refname, const struct object_id *oid)
{
	struct packed_ref_cache *packed_ref_cache = get_packed_ref_cache(refs);

	if (!is_lock_file_locked(&refs->packed_refs_lock))
		die("BUG: packed refs not locked");

	if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL))
		die("Reference has invalid format: '%s'", refname);

	add_ref_entry(get_packed_ref_dir(packed_ref_cache),
		      create_ref_entry(refname, oid, REF_ISPACKED));
}