int ref_transaction_create(struct ref_transaction *transaction,
			   const char *refname,
			   const unsigned char *new_sha1,
			   unsigned int flags, const char *msg,
			   struct strbuf *err)
{
	if (!new_sha1 || is_null_sha1(new_sha1))
		die("BUG: create called without valid new_sha1");
	return ref_transaction_update(transaction, refname, new_sha1,
				      null_sha1, flags, msg, err);
}