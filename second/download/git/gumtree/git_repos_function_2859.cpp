int ref_transaction_commit(struct ref_transaction *transaction,
			   struct strbuf *err)
{
	int ret = 0, i;
	int n = transaction->nr;
	struct ref_update **updates = transaction->updates;
	struct string_list refs_to_delete = STRING_LIST_INIT_NODUP;
	struct string_list_item *ref_to_delete;
	struct string_list affected_refnames = STRING_LIST_INIT_NODUP;

	assert(err);

	if (transaction->state != REF_TRANSACTION_OPEN)
		die("BUG: commit called for transaction that is not open");

	if (!n) {
		transaction->state = REF_TRANSACTION_CLOSED;
		return 0;
	}

	/* Fail if a refname appears more than once in the transaction: */
	for (i = 0; i < n; i++)
		string_list_append(&affected_refnames, updates[i]->refname);
	string_list_sort(&affected_refnames);
	if (ref_update_reject_duplicates(&affected_refnames, err)) {
		ret = TRANSACTION_GENERIC_ERROR;
		goto cleanup;
	}

	/*
	 * Acquire all locks, verify old values if provided, check
	 * that new values are valid, and write new values to the
	 * lockfiles, ready to be activated. Only keep one lockfile
	 * open at a time to avoid running out of file descriptors.
	 */
	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];

		if ((update->flags & REF_HAVE_NEW) &&
		    is_null_sha1(update->new_sha1))
			update->flags |= REF_DELETING;
		update->lock = lock_ref_sha1_basic(
				update->refname,
				((update->flags & REF_HAVE_OLD) ?
				 update->old_sha1 : NULL),
				&affected_refnames, NULL,
				update->flags,
				&update->type,
				err);
		if (!update->lock) {
			char *reason;

			ret = (errno == ENOTDIR)
				? TRANSACTION_NAME_CONFLICT
				: TRANSACTION_GENERIC_ERROR;
			reason = strbuf_detach(err, NULL);
			strbuf_addf(err, "cannot lock ref '%s': %s",
				    update->refname, reason);
			free(reason);
			goto cleanup;
		}
		if ((update->flags & REF_HAVE_NEW) &&
		    !(update->flags & REF_DELETING)) {
			int overwriting_symref = ((update->type & REF_ISSYMREF) &&
						  (update->flags & REF_NODEREF));

			if (!overwriting_symref &&
			    !hashcmp(update->lock->old_oid.hash, update->new_sha1)) {
				/*
				 * The reference already has the desired
				 * value, so we don't need to write it.
				 */
			} else if (write_ref_to_lockfile(update->lock,
							 update->new_sha1,
							 err)) {
				char *write_err = strbuf_detach(err, NULL);

				/*
				 * The lock was freed upon failure of
				 * write_ref_to_lockfile():
				 */
				update->lock = NULL;
				strbuf_addf(err,
					    "cannot update the ref '%s': %s",
					    update->refname, write_err);
				free(write_err);
				ret = TRANSACTION_GENERIC_ERROR;
				goto cleanup;
			} else {
				update->flags |= REF_NEEDS_COMMIT;
			}
		}
		if (!(update->flags & REF_NEEDS_COMMIT)) {
			/*
			 * We didn't have to write anything to the lockfile.
			 * Close it to free up the file descriptor:
			 */
			if (close_ref(update->lock)) {
				strbuf_addf(err, "Couldn't close %s.lock",
					    update->refname);
				goto cleanup;
			}
		}
	}

	/* Perform updates first so live commits remain referenced */
	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];

		if (update->flags & REF_NEEDS_COMMIT) {
			if (commit_ref_update(update->lock,
					      update->new_sha1, update->msg,
					      update->flags, err)) {
				/* freed by commit_ref_update(): */
				update->lock = NULL;
				ret = TRANSACTION_GENERIC_ERROR;
				goto cleanup;
			} else {
				/* freed by commit_ref_update(): */
				update->lock = NULL;
			}
		}
	}

	/* Perform deletes now that updates are safely completed */
	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];

		if (update->flags & REF_DELETING) {
			if (delete_ref_loose(update->lock, update->type, err)) {
				ret = TRANSACTION_GENERIC_ERROR;
				goto cleanup;
			}

			if (!(update->flags & REF_ISPRUNING))
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
	string_list_clear(&affected_refnames, 0);
	return ret;
}