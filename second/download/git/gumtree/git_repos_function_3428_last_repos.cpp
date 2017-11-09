struct ref_update *ref_transaction_add_update(
		struct ref_transaction *transaction,
		const char *refname, unsigned int flags,
		const unsigned char *new_sha1,
		const unsigned char *old_sha1,
		const char *msg)
{
	struct ref_update *update;

	if (transaction->state != REF_TRANSACTION_OPEN)
		die("BUG: update called for transaction that is not open");

	if ((flags & REF_ISPRUNING) && !(flags & REF_NODEREF))
		die("BUG: REF_ISPRUNING set without REF_NODEREF");

	FLEX_ALLOC_STR(update, refname, refname);
	ALLOC_GROW(transaction->updates, transaction->nr + 1, transaction->alloc);
	transaction->updates[transaction->nr++] = update;

	update->flags = flags;

	if (flags & REF_HAVE_NEW)
		hashcpy(update->new_oid.hash, new_sha1);
	if (flags & REF_HAVE_OLD)
		hashcpy(update->old_oid.hash, old_sha1);
	update->msg = xstrdup_or_null(msg);
	return update;
}