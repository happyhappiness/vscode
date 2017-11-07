int ref_transaction_commit(struct ref_transaction *transaction,
			   struct strbuf *err)
{
	int ret = 0, delnum = 0, i;
	const char **delnames;
	int n = transaction->nr;
	struct ref_update **updates = transaction->updates;

	assert(err);

	if (transaction->state != REF_TRANSACTION_OPEN)
		die("BUG: commit called for transaction that is not open");

	if (!n) {
		transaction->state = REF_TRANSACTION_CLOSED;
		return 0;
	}

	/* Allocate work space */
	delnames = xmalloc(sizeof(*delnames) * n);

	/* Copy, sort, and reject duplicate refs */
	qsort(updates, n, sizeof(*updates), ref_update_compare);
	if (ref_update_reject_duplicates(updates, n, err)) {
		ret = TRANSACTION_GENERIC_ERROR;
		goto cleanup;
	}

	/* Acquire all locks while verifying old values */
	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];
		int flags = update->flags;

		if (is_null_sha1(update->new_sha1))
			flags |= REF_DELETING;
		update->lock = lock_ref_sha1_basic(update->refname,
						   (update->have_old ?
						    update->old_sha1 :
						    NULL),
						   NULL,
						   flags,
						   &update->type);
		if (!update->lock) {
			ret = (errno == ENOTDIR)
				? TRANSACTION_NAME_CONFLICT
				: TRANSACTION_GENERIC_ERROR;
			strbuf_addf(err, "Cannot lock the ref '%s'.",
				    update->refname);
			goto cleanup;
		}
	}

	/* Perform updates first so live commits remain referenced */
	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];

		if (!is_null_sha1(update->new_sha1)) {
			if (write_ref_sha1(update->lock, update->new_sha1,
					   update->msg)) {
				update->lock = NULL; /* freed by write_ref_sha1 */
				strbuf_addf(err, "Cannot update the ref '%s'.",
					    update->refname);
				ret = TRANSACTION_GENERIC_ERROR;
				goto cleanup;
			}
			update->lock = NULL; /* freed by write_ref_sha1 */
		}
	}

	/* Perform deletes now that updates are safely completed */
	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];

		if (update->lock) {
			if (delete_ref_loose(update->lock, update->type, err)) {
				ret = TRANSACTION_GENERIC_ERROR;
				goto cleanup;
			}

			if (!(update->flags & REF_ISPRUNING))
				delnames[delnum++] = update->lock->ref_name;
		}
	}

	if (repack_without_refs(delnames, delnum, err)) {
		ret = TRANSACTION_GENERIC_ERROR;
		goto cleanup;
	}
	for (i = 0; i < delnum; i++)
		unlink_or_warn(git_path("logs/%s", delnames[i]));
	clear_loose_ref_cache(&ref_cache);

cleanup:
	transaction->state = REF_TRANSACTION_CLOSED;

	for (i = 0; i < n; i++)
		if (updates[i]->lock)
			unlock_ref(updates[i]->lock);
	free(delnames);
	return ret;
}