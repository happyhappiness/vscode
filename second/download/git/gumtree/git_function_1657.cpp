int ref_transaction_create(struct ref_transaction *transaction,
			   const char *refname,
			   const unsigned char *new_sha1,
			   int flags, const char *msg,
			   struct strbuf *err)
{
	struct ref_update *update;

	assert(err);

	if (transaction->state != REF_TRANSACTION_OPEN)
		die("BUG: create called for transaction that is not open");

	if (!new_sha1 || is_null_sha1(new_sha1))
		die("BUG: create ref with null new_sha1");

	if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
		strbuf_addf(err, "refusing to create ref with bad name %s",
			    refname);
		return -1;
	}

	update = add_update(transaction, refname);

	hashcpy(update->new_sha1, new_sha1);
	hashclr(update->old_sha1);
	update->flags = flags;
	update->have_old = 1;
	if (msg)
		update->msg = xstrdup(msg);
	return 0;
}