	 * so here we really only check that none of the references
	 * that we are creating already exists.
	 */
	if (for_each_rawref(ref_present, &affected_refnames))
		die("BUG: initial ref transaction called with existing refs");

	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];

		if ((update->flags & REF_HAVE_OLD) &&
		    !is_null_sha1(update->old_sha1))
			die("BUG: initial ref transaction with old_sha1 set");
		if (verify_refname_available(update->refname,
					     &affected_refnames, NULL,
