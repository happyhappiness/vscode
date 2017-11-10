int ref_transaction_commit(struct ref_transaction *transaction,
			   struct strbuf *err)
{
	int ret = 0, i;
	int n = transaction->nr;
	struct ref_update **updates = transaction->updates;
	struct string_list refs_to_delete = STRING_LIST_INIT_NODUP;
	struct string_list_item *ref_to_delete;

	assert(err);

	if (transaction->state != REF_TRANSACTION_OPEN)
		die("BUG: commit called for transaction that is not open");

	if (!n) {
		transaction->state = REF_TRANSACTION_CLOSED;
		return 0;
	}

	/* Copy, sort, and reject duplicate refs */
	qsort(updates, n, sizeof(*updates), ref_update_compare);
	if (ref_update_reject_duplicates(updates, n, err)) {
		ret = TRANSACTION_GENERIC_ERROR;
		goto cleanup;
	}

	/* Acquire all locks while verifying old values */
	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];
		unsigned int flags = update->flags;

		if ((flags & REF_HAVE_NEW) && is_null_sha1(update->new_sha1))
			flags |= REF_DELETING;
		update->lock = lock_ref_sha1_basic(
				update->refname,
				((update->flags & REF_HAVE_OLD) ?
				 update->old_sha1 : NULL),
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
		int flags = update->flags;

		if ((flags & REF_HAVE_NEW) && !is_null_sha1(update->new_sha1)) {
			int overwriting_symref = ((update->type & REF_ISSYMREF) &&
						  (update->flags & REF_NODEREF));

			if (!overwriting_symref
			    && !hashcmp(update->lock->old_sha1, update->new_sha1)) {
				/*
				 * The reference already has the desired
				 * value, so we don't need to write it.
				 */
				unlock_ref(update->lock);
				update->lock = NULL;
			} else if (write_ref_sha1(update->lock, update->new_sha1,
						  update->msg)) {
				update->lock = NULL; /* freed by write_ref_sha1 */
				strbuf_addf(err, "Cannot update the ref '%s'.",
					    update->refname);
				ret = TRANSACTION_GENERIC_ERROR;
				goto cleanup;
			} else {
				/* freed by write_ref_sha1(): */
				update->lock = NULL;
			}
		}
	}

	/* Perform deletes now that updates are safely completed */
	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];
		int flags = update->flags;

		if ((flags & REF_HAVE_NEW) && is_null_sha1(update->new_sha1)) {
			if (delete_ref_loose(update->lock, update->type, err)) {
				ret = TRANSACTION_GENERIC_ERROR;
				goto cleanup;
			}

			if (!(flags & REF_ISPRUNING))
				string_list_append(&refs_to_delete,
						   update->lock->ref_name);
		}
	}

	if (repack_without_refs(&refs_to_delete, err)) {
		ret = TRANSACTION_GENERIC_ERROR;
		goto cleanup;
	}
	for_each_string_list_item(ref_to_delete, &refs_to_delete)
		unlink_or_warn(git_path("logs/%s", ref_to_delete->string));
	clear_loose_ref_cache(&ref_cache);

cleanup:
	transaction->state = REF_TRANSACTION_CLOSED;

	for (i = 0; i < n; i++)
		if (updates[i]->lock)
			unlock_ref(updates[i]->lock);
	string_list_clear(&refs_to_delete, 0);
	return ret;
}