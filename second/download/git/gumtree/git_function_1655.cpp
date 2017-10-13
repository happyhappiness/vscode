int ref_transaction_update(struct ref_transaction *transaction,
			   const char *refname,
			   const unsigned char *new_sha1,
			   const unsigned char *old_sha1,
			   int flags, int have_old, const char *msg,
			   struct strbuf *err)
{
	struct ref_update *update;

	assert(err);

	if (transaction->state != REF_TRANSACTION_OPEN)
		die("BUG: update called for transaction that is not open");

	if (have_old && !old_sha1)
		die("BUG: have_old is true but old_sha1 is NULL");

	if (!is_null_sha1(new_sha1) &&
	    check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
		strbuf_addf(err, "refusing to update ref with bad name %s",
			    refname);
		return -1;
	}

	update = add_update(transaction, refname);
	hashcpy(update->new_sha1, new_sha1);
	update->flags = flags;
	update->have_old = have_old;
	if (have_old)
		hashcpy(update->old_sha1, old_sha1);
	if (msg)
		update->msg = xstrdup(msg);
	return 0;
}