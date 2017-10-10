{
	struct ref_lock *lock;
	lock = lock_any_ref_for_update(refname, oldval, flags, type_p);
	if (!lock) {
		const char *str = "Cannot lock the ref '%s'.";
		switch (onerr) {
		case MSG_ON_ERR: error(str, refname); break;
		case DIE_ON_ERR: die(str, refname); break;
		case QUIET_ON_ERR: break;
		}
	}
	return lock;
}

static int update_ref_write(const char *action, const char *refname,
			    const unsigned char *sha1, struct ref_lock *lock,
			    enum action_on_err onerr)
{
	if (write_ref_sha1(lock, sha1, action) < 0) {
		const char *str = "Cannot update the ref '%s'.";
		switch (onerr) {
		case MSG_ON_ERR: error(str, refname); break;
		case DIE_ON_ERR: die(str, refname); break;
		case QUIET_ON_ERR: break;
		}
		return 1;
	}
	return 0;
}

int update_ref(const char *action, const char *refname,
	       const unsigned char *sha1, const unsigned char *oldval,
	       int flags, enum action_on_err onerr)
{
	struct ref_lock *lock;
	lock = update_ref_lock(refname, oldval, flags, NULL, onerr);
	if (!lock)
		return 1;
	return update_ref_write(action, refname, sha1, lock, onerr);
}

static int ref_update_compare(const void *r1, const void *r2)
{
	const struct ref_update * const *u1 = r1;
	const struct ref_update * const *u2 = r2;
	return strcmp((*u1)->ref_name, (*u2)->ref_name);
}

static int ref_update_reject_duplicates(struct ref_update **updates, int n,
					enum action_on_err onerr)
{
	int i;
	for (i = 1; i < n; i++)
		if (!strcmp(updates[i - 1]->ref_name, updates[i]->ref_name)) {
			const char *str =
				"Multiple updates for ref '%s' not allowed.";
			switch (onerr) {
			case MSG_ON_ERR:
				error(str, updates[i]->ref_name); break;
			case DIE_ON_ERR:
				die(str, updates[i]->ref_name); break;
			case QUIET_ON_ERR:
				break;
			}
			return 1;
		}
	return 0;
}

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

char *shorten_unambiguous_ref(const char *refname, int strict)
{
