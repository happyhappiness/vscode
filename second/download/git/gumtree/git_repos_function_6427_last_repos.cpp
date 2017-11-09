static int files_delete_refs(struct ref_store *ref_store, const char *msg,
			     struct string_list *refnames, unsigned int flags)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE, "delete_refs");
	struct strbuf err = STRBUF_INIT;
	int i, result = 0;

	if (!refnames->nr)
		return 0;

	result = repack_without_refs(refs, refnames, &err);
	if (result) {
		/*
		 * If we failed to rewrite the packed-refs file, then
		 * it is unsafe to try to remove loose refs, because
		 * doing so might expose an obsolete packed value for
		 * a reference that might even point at an object that
		 * has been garbage collected.
		 */
		if (refnames->nr == 1)
			error(_("could not delete reference %s: %s"),
			      refnames->items[0].string, err.buf);
		else
			error(_("could not delete references: %s"), err.buf);

		goto out;
	}

	for (i = 0; i < refnames->nr; i++) {
		const char *refname = refnames->items[i].string;

		if (refs_delete_ref(&refs->base, msg, refname, NULL, flags))
			result |= error(_("could not remove reference %s"), refname);
	}

out:
	strbuf_release(&err);
	return result;
}