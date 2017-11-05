int ref_transaction_delete(struct ref_transaction *transaction,
			   const char *refname,
			   const unsigned char *old_sha1,
			   int flags, int have_old, const char *msg,
			   struct strbuf *err)
{
	struct ref_update *update;

	assert(err);

	if (transaction->state != REF_TRANSACTION_OPEN)
		die("BUG: delete called for transaction that is not open");

	if (have_old && !old_sha1)
		die("BUG: have_old is true but old_sha1 is NULL");

	update = add_update(transaction, refname);
	update->flags = flags;
	update->have_old = have_old;
	if (have_old) {
		assert(!is_null_sha1(old_sha1));
		hashcpy(update->old_sha1, old_sha1);
	}
	if (msg)
		update->msg = xstrdup(msg);
	return 0;
}