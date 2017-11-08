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