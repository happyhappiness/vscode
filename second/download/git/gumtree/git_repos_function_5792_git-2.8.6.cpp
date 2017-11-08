int verify_refname_available(const char *newname,
			     struct string_list *extras,
			     struct string_list *skip,
			     struct strbuf *err)
{
	struct ref_dir *packed_refs = get_packed_refs(&ref_cache);
	struct ref_dir *loose_refs = get_loose_refs(&ref_cache);

	if (verify_refname_available_dir(newname, extras, skip,
					 packed_refs, err) ||
	    verify_refname_available_dir(newname, extras, skip,
					 loose_refs, err))
		return -1;

	return 0;
}