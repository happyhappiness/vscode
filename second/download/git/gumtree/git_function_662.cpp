static int get_short_sha1(const char *name, int len, unsigned char *sha1,
			  unsigned flags)
{
	int status;
	struct disambiguate_state ds;
	int quietly = !!(flags & GET_SHA1_QUIETLY);

	if (init_object_disambiguation(name, len, &ds) < 0)
		return -1;

	if (HAS_MULTI_BITS(flags & GET_SHA1_DISAMBIGUATORS))
		die("BUG: multiple get_short_sha1 disambiguator flags");

	if (flags & GET_SHA1_COMMIT)
		ds.fn = disambiguate_commit_only;
	else if (flags & GET_SHA1_COMMITTISH)
		ds.fn = disambiguate_committish_only;
	else if (flags & GET_SHA1_TREE)
		ds.fn = disambiguate_tree_only;
	else if (flags & GET_SHA1_TREEISH)
		ds.fn = disambiguate_treeish_only;
	else if (flags & GET_SHA1_BLOB)
		ds.fn = disambiguate_blob_only;
	else
		ds.fn = default_disambiguate_hint;

	find_short_object_filename(&ds);
	find_short_packed_object(&ds);
	status = finish_object_disambiguation(&ds, sha1);

	if (!quietly && (status == SHORT_NAME_AMBIGUOUS)) {
		error(_("short SHA1 %s is ambiguous"), ds.hex_pfx);

		/*
		 * We may still have ambiguity if we simply saw a series of
		 * candidates that did not satisfy our hint function. In
		 * that case, we still want to show them, so disable the hint
		 * function entirely.
		 */
		if (!ds.ambiguous)
			ds.fn = NULL;

		advise(_("The candidates are:"));
		for_each_abbrev(ds.hex_pfx, show_ambiguous_object, &ds);
	}

	return status;
}