}

static int ref_update_reject_duplicates(struct ref_update **updates, int n,
					struct strbuf *err)
{
	int i;
	for (i = 1; i < n; i++)
		if (!strcmp(updates[i - 1]->refname, updates[i]->refname)) {
			const char *str =
				"Multiple updates for ref '%s' not allowed.";
			if (err)
				strbuf_addf(err, str, updates[i]->refname);

			return 1;
		}
	return 0;
}

int ref_transaction_commit(struct ref_transaction *transaction,
			   const char *msg, struct strbuf *err)
{
	int ret = 0, delnum = 0, i;
	const char **delnames;
	int n = transaction->nr;
	struct ref_update **updates = transaction->updates;

	if (!n)
		return 0;

	/* Allocate work space */
	delnames = xmalloc(sizeof(*delnames) * n);

	/* Copy, sort, and reject duplicate refs */
	qsort(updates, n, sizeof(*updates), ref_update_compare);
	ret = ref_update_reject_duplicates(updates, n, err);
	if (ret)
		goto cleanup;

	/* Acquire all locks while verifying old values */
	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];

		update->lock = update_ref_lock(update->refname,
					       (update->have_old ?
						update->old_sha1 : NULL),
					       update->flags,
					       &update->type,
					       UPDATE_REFS_QUIET_ON_ERR);
		if (!update->lock) {
			if (err)
				strbuf_addf(err, "Cannot lock the ref '%s'.",
					    update->refname);
			ret = 1;
			goto cleanup;
		}
	}

	/* Perform updates first so live commits remain referenced */
	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];

		if (!is_null_sha1(update->new_sha1)) {
			ret = update_ref_write(msg,
					       update->refname,
					       update->new_sha1,
					       update->lock, err,
					       UPDATE_REFS_QUIET_ON_ERR);
			update->lock = NULL; /* freed by update_ref_write */
			if (ret)
				goto cleanup;
		}
	}

	/* Perform deletes now that updates are safely completed */
	for (i = 0; i < n; i++) {
		struct ref_update *update = updates[i];

		if (update->lock) {
			delnames[delnum++] = update->lock->ref_name;
			ret |= delete_ref_loose(update->lock, update->type);
		}
	}

	ret |= repack_without_refs(delnames, delnum, err);
	for (i = 0; i < delnum; i++)
		unlink_or_warn(git_path("logs/%s", delnames[i]));
	clear_loose_ref_cache(&ref_cache);

cleanup:
	for (i = 0; i < n; i++)
		if (updates[i]->lock)
			unlock_ref(updates[i]->lock);
	free(delnames);
	return ret;
}
