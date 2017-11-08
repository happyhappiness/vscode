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