int verify_refname_available(const char *refname,
			     const struct string_list *extra,
			     const struct string_list *skip,
			     struct strbuf *err)
{
	struct ref_store *refs = get_ref_store(NULL);

	return refs->be->verify_refname_available(refs, refname, extra, skip, err);
}