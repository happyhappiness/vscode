int delete_refs(struct string_list *refnames)
{
	struct strbuf err = STRBUF_INIT;
	int i, result = 0;

	if (!refnames->nr)
		return 0;

	result = repack_without_refs(refnames, &err);
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

		if (delete_ref(refname, NULL, 0))
			result |= error(_("could not remove reference %s"), refname);
	}

out:
	strbuf_release(&err);
	return result;
}