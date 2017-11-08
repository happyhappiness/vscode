static int lock_ref_for_update(struct files_ref_store *refs,
			       struct ref_update *update,
			       struct ref_transaction *transaction,
			       const char *head_ref,
			       struct string_list *affected_refnames,
			       struct strbuf *err)
{
	struct strbuf referent = STRBUF_INIT;
	int mustexist = (update->flags & REF_HAVE_OLD) &&
		!is_null_sha1(update->old_sha1);
	int ret;
	struct ref_lock *lock;

	files_assert_main_repository(refs, "lock_ref_for_update");

	if ((update->flags & REF_HAVE_NEW) && is_null_sha1(update->new_sha1))
		update->flags |= REF_DELETING;

	if (head_ref) {
		ret = split_head_update(update, transaction, head_ref,
					affected_refnames, err);
		if (ret)
			return ret;
	}

	ret = lock_raw_ref(refs, update->refname, mustexist,
			   affected_refnames, NULL,
			   &lock, &referent,
			   &update->type, err);
	if (ret) {
		char *reason;

		reason = strbuf_detach(err, NULL);
		strbuf_addf(err, "cannot lock ref '%s': %s",
			    original_update_refname(update), reason);
		free(reason);
		return ret;
	}

	update->backend_data = lock;

	if (update->type & REF_ISSYMREF) {
		if (update->flags & REF_NODEREF) {
			/*
			 * We won't be reading the referent as part of
			 * the transaction, so we have to read it here
			 * to record and possibly check old_sha1:
			 */
			if (refs_read_ref_full(&refs->base,
					       referent.buf, 0,
					       lock->old_oid.hash, NULL)) {
				if (update->flags & REF_HAVE_OLD) {
					strbuf_addf(err, "cannot lock ref '%s': "
						    "error reading reference",
						    original_update_refname(update));
					return -1;
				}
			} else if (check_old_oid(update, &lock->old_oid, err)) {
				return TRANSACTION_GENERIC_ERROR;
			}
		} else {
			/*
			 * Create a new update for the reference this
			 * symref is pointing at. Also, we will record
			 * and verify old_sha1 for this update as part
			 * of processing the split-off update, so we
			 * don't have to do it here.
			 */
			ret = split_symref_update(refs, update,
						  referent.buf, transaction,
						  affected_refnames, err);
			if (ret)
				return ret;
		}
	} else {
		struct ref_update *parent_update;

		if (check_old_oid(update, &lock->old_oid, err))
			return TRANSACTION_GENERIC_ERROR;

		/*
		 * If this update is happening indirectly because of a
		 * symref update, record the old SHA-1 in the parent
		 * update:
		 */
		for (parent_update = update->parent_update;
		     parent_update;
		     parent_update = parent_update->parent_update) {
			struct ref_lock *parent_lock = parent_update->backend_data;
			oidcpy(&parent_lock->old_oid, &lock->old_oid);
		}
	}

	if ((update->flags & REF_HAVE_NEW) &&
	    !(update->flags & REF_DELETING) &&
	    !(update->flags & REF_LOG_ONLY)) {
		if (!(update->type & REF_ISSYMREF) &&
		    !hashcmp(lock->old_oid.hash, update->new_sha1)) {
			/*
			 * The reference already has the desired
			 * value, so we don't need to write it.
			 */
		} else if (write_ref_to_lockfile(lock, update->new_sha1,
						 err)) {
			char *write_err = strbuf_detach(err, NULL);

			/*
			 * The lock was freed upon failure of
			 * write_ref_to_lockfile():
			 */
			update->backend_data = NULL;
			strbuf_addf(err,
				    "cannot update ref '%s': %s",
				    update->refname, write_err);
			free(write_err);
			return TRANSACTION_GENERIC_ERROR;
		} else {
			update->flags |= REF_NEEDS_COMMIT;
		}
	}
	if (!(update->flags & REF_NEEDS_COMMIT)) {
		/*
		 * We didn't call write_ref_to_lockfile(), so
		 * the lockfile is still open. Close it to
		 * free up the file descriptor:
		 */
		if (close_ref(lock)) {
			strbuf_addf(err, "couldn't close '%s.lock'",
				    update->refname);
			return TRANSACTION_GENERIC_ERROR;
		}
	}
	return 0;
}