static int files_initial_transaction_commit(struct ref_store *ref_store,
					    struct ref_transaction *transaction,
					    struct strbuf *err)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE,
			       "initial_ref_transaction_commit");
	size_t i;
	int ret = 0;
	struct string_list affected_refnames = STRING_LIST_INIT_NODUP;

	assert(err);

	if (transaction->state != REF_TRANSACTION_OPEN)
		die("BUG: commit called for transaction that is not open");

	/* Fail if a refname appears more than once in the transaction: */
	for (i = 0; i < transaction->nr; i++)
		string_list_append(&affected_refnames,
				   transaction->updates[i]->refname);
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
	if (refs_for_each_rawref(&refs->base, ref_present,
				 &affected_refnames))
		die("BUG: initial ref transaction called with existing refs");

	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];

		if ((update->flags & REF_HAVE_OLD) &&
		    !is_null_oid(&update->old_oid))
			die("BUG: initial ref transaction with old_sha1 set");
		if (refs_verify_refname_available(&refs->base, update->refname,
						  &affected_refnames, NULL,
						  err)) {
			ret = TRANSACTION_NAME_CONFLICT;
			goto cleanup;
		}
	}

	if (lock_packed_refs(refs, 0)) {
		strbuf_addf(err, "unable to lock packed-refs file: %s",
			    strerror(errno));
		ret = TRANSACTION_GENERIC_ERROR;
		goto cleanup;
	}

	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];

		if ((update->flags & REF_HAVE_NEW) &&
		    !is_null_oid(&update->new_oid))
			add_packed_ref(refs, update->refname,
				       &update->new_oid);
	}

	if (commit_packed_refs(refs)) {
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