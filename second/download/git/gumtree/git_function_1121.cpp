int refs_verify_refname_available(struct ref_store *refs,
				  const char *refname,
				  const struct string_list *extras,
				  const struct string_list *skip,
				  struct strbuf *err)
{
	const char *slash;
	const char *extra_refname;
	struct strbuf dirname = STRBUF_INIT;
	struct strbuf referent = STRBUF_INIT;
	struct object_id oid;
	unsigned int type;
	struct ref_iterator *iter;
	int ok;
	int ret = -1;

	/*
	 * For the sake of comments in this function, suppose that
	 * refname is "refs/foo/bar".
	 */

	assert(err);

	strbuf_grow(&dirname, strlen(refname) + 1);
	for (slash = strchr(refname, '/'); slash; slash = strchr(slash + 1, '/')) {
		/* Expand dirname to the new prefix, not including the trailing slash: */
		strbuf_add(&dirname, refname + dirname.len, slash - refname - dirname.len);

		/*
		 * We are still at a leading dir of the refname (e.g.,
		 * "refs/foo"; if there is a reference with that name,
		 * it is a conflict, *unless* it is in skip.
		 */
		if (skip && string_list_has_string(skip, dirname.buf))
			continue;

		if (!refs_read_raw_ref(refs, dirname.buf, oid.hash, &referent, &type)) {
			strbuf_addf(err, "'%s' exists; cannot create '%s'",
				    dirname.buf, refname);
			goto cleanup;
		}

		if (extras && string_list_has_string(extras, dirname.buf)) {
			strbuf_addf(err, "cannot process '%s' and '%s' at the same time",
				    refname, dirname.buf);
			goto cleanup;
		}
	}

	/*
	 * We are at the leaf of our refname (e.g., "refs/foo/bar").
	 * There is no point in searching for a reference with that
	 * name, because a refname isn't considered to conflict with
	 * itself. But we still need to check for references whose
	 * names are in the "refs/foo/bar/" namespace, because they
	 * *do* conflict.
	 */
	strbuf_addstr(&dirname, refname + dirname.len);
	strbuf_addch(&dirname, '/');

	iter = refs_ref_iterator_begin(refs, dirname.buf, 0,
				       DO_FOR_EACH_INCLUDE_BROKEN);
	while ((ok = ref_iterator_advance(iter)) == ITER_OK) {
		if (skip &&
		    string_list_has_string(skip, iter->refname))
			continue;

		strbuf_addf(err, "'%s' exists; cannot create '%s'",
			    iter->refname, refname);
		ref_iterator_abort(iter);
		goto cleanup;
	}

	if (ok != ITER_DONE)
		die("BUG: error while iterating over references");

	extra_refname = find_descendant_ref(dirname.buf, extras, skip);
	if (extra_refname)
		strbuf_addf(err, "cannot process '%s' and '%s' at the same time",
			    refname, extra_refname);
	else
		ret = 0;

cleanup:
	strbuf_release(&referent);
	strbuf_release(&dirname);
	return ret;
}