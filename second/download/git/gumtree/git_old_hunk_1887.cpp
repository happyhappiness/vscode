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
