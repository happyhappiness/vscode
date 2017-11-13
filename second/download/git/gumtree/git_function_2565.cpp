int initial_ref_transaction_commit(struct ref_transaction *transaction,
				   struct strbuf *err)
{
	struct ref_dir *loose_refs = get_loose_refs(&ref_cache);
	struct ref_dir *packed_refs = get_packed_refs(&ref_cache);
	int ret = 0, i;
	int n = transaction->nr;
	struct ref_update **updates = transaction->updates;
	struct string_list affected_refnames = STRING_LIST_INIT_NODUP;

	assert(err);

	if (transaction->state != REF_TRANSACTION_OPEN)
		die("BUG: commit called for transaction that is not open");

	/* Fail if a refname appears more than once in the transaction: */
	for (i = 0; i < n; i++)
		string_list_append(&affected_refnames, updates[i]->refname);
	string_list_sort(&affected_refnames);
	if (ref_update_reject_duplicates(&affected_refnames, err)) {
		ret = TRANSACTION_GENERIC_ERROR;
		goto cleanup;
	}

	/*
	 * It's really undefined to call this function in an active
	 * repository or when there are existing references: we are
	 * only locking and changing packed-refs, so (1) any
	 * simultaneous processes might try to change a reference at
	 * the same time we do, and (2) any existing loose versions of
	 * the references that we are setting would have precedence
	 * over our values. But some remote helpers create the remote
	 * "HEAD" and "master" branches before calling this function,
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
					     loose_refs, err) ||
		    verify_refname_available(update->refname,
					     &affected_refnames, NULL,
					     packed_refs, err)) {
			ret = TRANSACTION_NAME_CONFLICT;
			goto cleanup;
		}
	}

	if (lock_packed_refs(0)) {
		strbuf_addf(err, "unable to lock packed-refs file: %s",
			    strerror(errno));
		ret = TRANSACTION_GENERIC_ERROR;
		goto cleanup;
	}

	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];

		if ((update->flags & REF_HAVE_NEW) &&
		    !is_null_sha1(update->new_sha1))
			add_packed_ref(update->refname, update->new_sha1);
	}

	if (commit_packed_refs()) {
		strbuf_addf(err, "unable to commit packed-refs file: %s",
			    strerror(errno));
		ret = TRANSACTION_GENERIC_ERROR;
		goto cleanup;
	}

cleanup:
	transaction->state = REF_TRANSACTION_CLOSED;
	string_list_clear(&affected_refnames, 0);
	return ret;
}