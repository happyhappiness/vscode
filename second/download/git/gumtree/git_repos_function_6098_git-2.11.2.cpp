static int files_verify_refname_available(struct ref_store *ref_store,
					  const char *newname,
					  const struct string_list *extras,
					  const struct string_list *skip,
					  struct strbuf *err)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, 1, "verify_refname_available");
	struct ref_dir *packed_refs = get_packed_refs(refs);
	struct ref_dir *loose_refs = get_loose_refs(refs);

	if (verify_refname_available_dir(newname, extras, skip,
					 packed_refs, err) ||
	    verify_refname_available_dir(newname, extras, skip,
					 loose_refs, err))
		return -1;

	return 0;
}