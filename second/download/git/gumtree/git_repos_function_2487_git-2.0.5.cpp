int update_refs(const char *action, const struct ref_update **updates_orig,
		int n, enum action_on_err onerr)
{
	int ret = 0, delnum = 0, i;
	struct ref_update **updates;
	int *types;
	struct ref_lock **locks;
	const char **delnames;

	if (!updates_orig || !n)
		return 0;

	/* Allocate work space */
	updates = xmalloc(sizeof(*updates) * n);
	types = xmalloc(sizeof(*types) * n);
	locks = xcalloc(n, sizeof(*locks));
	delnames = xmalloc(sizeof(*delnames) * n);

	/* Copy, sort, and reject duplicate refs */
	memcpy(updates, updates_orig, sizeof(*updates) * n);
	qsort(updates, n, sizeof(*updates), ref_update_compare);
	ret = ref_update_reject_duplicates(updates, n, onerr);
	if (ret)
		goto cleanup;

	/* Acquire all locks while verifying old values */
	for (i = 0; i < n; i++) {
		locks[i] = update_ref_lock(updates[i]->ref_name,
					   (updates[i]->have_old ?
					    updates[i]->old_sha1 : NULL),
					   updates[i]->flags,
					   &types[i], onerr);
		if (!locks[i]) {
			ret = 1;
			goto cleanup;
		}
	}

	/* Perform updates first so live commits remain referenced */
	for (i = 0; i < n; i++)
		if (!is_null_sha1(updates[i]->new_sha1)) {
			ret = update_ref_write(action,
					       updates[i]->ref_name,
					       updates[i]->new_sha1,
					       locks[i], onerr);
			locks[i] = NULL; /* freed by update_ref_write */
			if (ret)
				goto cleanup;
		}

	/* Perform deletes now that updates are safely completed */
	for (i = 0; i < n; i++)
		if (locks[i]) {
			delnames[delnum++] = locks[i]->ref_name;
			ret |= delete_ref_loose(locks[i], types[i]);
		}
	ret |= repack_without_refs(delnames, delnum);
	for (i = 0; i < delnum; i++)
		unlink_or_warn(git_path("logs/%s", delnames[i]));
	clear_loose_ref_cache(&ref_cache);

cleanup:
	for (i = 0; i < n; i++)
		if (locks[i])
			unlock_ref(locks[i]);
	free(updates);
	free(types);
	free(locks);
	free(delnames);
	return ret;
}