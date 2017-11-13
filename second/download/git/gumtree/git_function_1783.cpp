int ref_transaction_verify(struct ref_transaction *transaction,
			   const char *refname,
			   const unsigned char *old_sha1,
			   unsigned int flags,
			   struct strbuf *err)
{
	if (!old_sha1)
		die("BUG: verify called with old_sha1 set to NULL");
	return ref_transaction_update(transaction, refname,
				      NULL, old_sha1,
				      flags, NULL, err);
}