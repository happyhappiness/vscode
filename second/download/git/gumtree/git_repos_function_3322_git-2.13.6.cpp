int refs_rename_ref_available(struct ref_store *refs,
			      const char *old_refname,
			      const char *new_refname)
{
	struct string_list skip = STRING_LIST_INIT_NODUP;
	struct strbuf err = STRBUF_INIT;
	int ok;

	string_list_insert(&skip, old_refname);
	ok = !refs_verify_refname_available(refs, new_refname,
					    NULL, &skip, &err);
	if (!ok)
		error("%s", err.buf);

	string_list_clear(&skip, 0);
	strbuf_release(&err);
	return ok;
}