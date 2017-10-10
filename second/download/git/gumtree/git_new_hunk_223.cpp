{
	struct ref_lock *lock;
	lock = lock_any_ref_for_update(refname, oldval, flags, type_p);
	if (!lock) {
		const char *str = "Cannot lock the ref '%s'.";
		switch (onerr) {
		case UPDATE_REFS_MSG_ON_ERR: error(str, refname); break;
		case UPDATE_REFS_DIE_ON_ERR: die(str, refname); break;
		case UPDATE_REFS_QUIET_ON_ERR: break;
		}
	}
	return lock;
}

static int update_ref_write(const char *action, const char *refname,
			    const unsigned char *sha1, struct ref_lock *lock,
			    struct strbuf *err, enum action_on_err onerr)
{
	if (write_ref_sha1(lock, sha1, action) < 0) {
		const char *str = "Cannot update the ref '%s'.";
		if (err)
			strbuf_addf(err, str, refname);

		switch (onerr) {
		case UPDATE_REFS_MSG_ON_ERR: error(str, refname); break;
		case UPDATE_REFS_DIE_ON_ERR: die(str, refname); break;
		case UPDATE_REFS_QUIET_ON_ERR: break;
		}
		return 1;
	}
	return 0;
}

/**
 * Information needed for a single ref update.  Set new_sha1 to the
 * new value or to zero to delete the ref.  To check the old value
 * while locking the ref, set have_old to 1 and set old_sha1 to the
 * value or to zero to ensure the ref does not exist before update.
 */
struct ref_update {
	unsigned char new_sha1[20];
	unsigned char old_sha1[20];
	int flags; /* REF_NODEREF? */
	int have_old; /* 1 if old_sha1 is valid, 0 otherwise */
	struct ref_lock *lock;
	int type;
	const char refname[FLEX_ARRAY];
};

/*
 * Data structure for holding a reference transaction, which can
 * consist of checks and updates to multiple references, carried out
 * as atomically as possible.  This structure is opaque to callers.
 */
struct ref_transaction {
	struct ref_update **updates;
	size_t alloc;
	size_t nr;
};

struct ref_transaction *ref_transaction_begin(void)
{
	return xcalloc(1, sizeof(struct ref_transaction));
}

void ref_transaction_free(struct ref_transaction *transaction)
{
	int i;

	if (!transaction)
		return;

	for (i = 0; i < transaction->nr; i++)
		free(transaction->updates[i]);

	free(transaction->updates);
	free(transaction);
}

static struct ref_update *add_update(struct ref_transaction *transaction,
				     const char *refname)
{
	size_t len = strlen(refname);
	struct ref_update *update = xcalloc(1, sizeof(*update) + len + 1);

	strcpy((char *)update->refname, refname);
	ALLOC_GROW(transaction->updates, transaction->nr + 1, transaction->alloc);
	transaction->updates[transaction->nr++] = update;
	return update;
}

int ref_transaction_update(struct ref_transaction *transaction,
			   const char *refname,
			   const unsigned char *new_sha1,
			   const unsigned char *old_sha1,
			   int flags, int have_old,
			   struct strbuf *err)
{
	struct ref_update *update;

	if (have_old && !old_sha1)
		die("BUG: have_old is true but old_sha1 is NULL");

	update = add_update(transaction, refname);
	hashcpy(update->new_sha1, new_sha1);
	update->flags = flags;
	update->have_old = have_old;
	if (have_old)
		hashcpy(update->old_sha1, old_sha1);
	return 0;
}

void ref_transaction_create(struct ref_transaction *transaction,
			    const char *refname,
			    const unsigned char *new_sha1,
			    int flags)
{
	struct ref_update *update = add_update(transaction, refname);

	assert(!is_null_sha1(new_sha1));
	hashcpy(update->new_sha1, new_sha1);
	hashclr(update->old_sha1);
	update->flags = flags;
	update->have_old = 1;
}

void ref_transaction_delete(struct ref_transaction *transaction,
			    const char *refname,
			    const unsigned char *old_sha1,
			    int flags, int have_old)
{
	struct ref_update *update = add_update(transaction, refname);

	update->flags = flags;
	update->have_old = have_old;
	if (have_old) {
		assert(!is_null_sha1(old_sha1));
		hashcpy(update->old_sha1, old_sha1);
	}
}

int update_ref(const char *action, const char *refname,
	       const unsigned char *sha1, const unsigned char *oldval,
	       int flags, enum action_on_err onerr)
{
	struct ref_lock *lock;
	lock = update_ref_lock(refname, oldval, flags, NULL, onerr);
	if (!lock)
		return 1;
	return update_ref_write(action, refname, sha1, lock, NULL, onerr);
}

static int ref_update_compare(const void *r1, const void *r2)
{
	const struct ref_update * const *u1 = r1;
	const struct ref_update * const *u2 = r2;
	return strcmp((*u1)->refname, (*u2)->refname);
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

char *shorten_unambiguous_ref(const char *refname, int strict)
{
