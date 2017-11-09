static int files_transaction_finish(struct ref_store *ref_store,
				    struct ref_transaction *transaction,
				    struct strbuf *err)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, 0, "ref_transaction_finish");
	size_t i;
	int ret = 0;
	struct string_list refs_to_delete = STRING_LIST_INIT_NODUP;
	struct string_list_item *ref_to_delete;
	struct strbuf sb = STRBUF_INIT;

	assert(err);

	if (!transaction->nr) {
		transaction->state = REF_TRANSACTION_CLOSED;
		return 0;
	}

	/* Perform updates first so live commits remain referenced */
	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];
		struct ref_lock *lock = update->backend_data;

		if (update->flags & REF_NEEDS_COMMIT ||
		    update->flags & REF_LOG_ONLY) {
			if (files_log_ref_write(refs,
						lock->ref_name,
						&lock->old_oid,
						&update->new_oid,
						update->msg, update->flags,
						err)) {
				char *old_msg = strbuf_detach(err, NULL);

				strbuf_addf(err, "cannot update the ref '%s': %s",
					    lock->ref_name, old_msg);
				free(old_msg);
				unlock_ref(lock);
				update->backend_data = NULL;
				ret = TRANSACTION_GENERIC_ERROR;
				goto cleanup;
			}
		}
		if (update->flags & REF_NEEDS_COMMIT) {
			clear_loose_ref_cache(refs);
			if (commit_ref(lock)) {
				strbuf_addf(err, "couldn't set '%s'", lock->ref_name);
				unlock_ref(lock);
				update->backend_data = NULL;
				ret = TRANSACTION_GENERIC_ERROR;
				goto cleanup;
			}
		}
	}
	/* Perform deletes now that updates are safely completed */
	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];
		struct ref_lock *lock = update->backend_data;

		if (update->flags & REF_DELETING &&
		    !(update->flags & REF_LOG_ONLY)) {
			if (!(update->type & REF_ISPACKED) ||
			    update->type & REF_ISSYMREF) {
				/* It is a loose reference. */
				strbuf_reset(&sb);
				files_ref_path(refs, &sb, lock->ref_name);
				if (unlink_or_msg(sb.buf, err)) {
					ret = TRANSACTION_GENERIC_ERROR;
					goto cleanup;
				}
				update->flags |= REF_DELETED_LOOSE;
			}

			if (!(update->flags & REF_ISPRUNING))
				string_list_append(&refs_to_delete,
						   lock->ref_name);
		}
	}

	if (repack_without_refs(refs, &refs_to_delete, err)) {
		ret = TRANSACTION_GENERIC_ERROR;
		goto cleanup;
	}

	/* Delete the reflogs of any references that were deleted: */
	for_each_string_list_item(ref_to_delete, &refs_to_delete) {
		strbuf_reset(&sb);
		files_reflog_path(refs, &sb, ref_to_delete->string);
		if (!unlink_or_warn(sb.buf))
			try_remove_empty_parents(refs, ref_to_delete->string,
						 REMOVE_EMPTY_PARENTS_REFLOG);
	}

	clear_loose_ref_cache(refs);

cleanup:
	files_transaction_cleanup(transaction);

	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];

		if (update->flags & REF_DELETED_LOOSE) {
			/*
			 * The loose reference was deleted. Delete any
			 * empty parent directories. (Note that this
			 * can only work because we have already
			 * removed the lockfile.)
			 */
			try_remove_empty_parents(refs, update->refname,
						 REMOVE_EMPTY_PARENTS_REF);
		}
	}

	strbuf_release(&sb);
	string_list_clear(&refs_to_delete, 0);
	return ret;
}