int ref_transaction_update(struct ref_transaction *transaction,
			   const char *refname,
			   const unsigned char *new_sha1,
			   const unsigned char *old_sha1,
			   unsigned int flags, const char *msg,
			   struct strbuf *err)
{
	assert(err);

	if ((new_sha1 && !is_null_sha1(new_sha1)) ?
	    check_refname_format(refname, REFNAME_ALLOW_ONELEVEL) :
	    !refname_is_safe(refname)) {
		strbuf_addf(err, "refusing to update ref with bad name '%s'",
			    refname);
		return -1;
	}

	flags |= (new_sha1 ? REF_HAVE_NEW : 0) | (old_sha1 ? REF_HAVE_OLD : 0);

	ref_transaction_add_update(transaction, refname, flags,
				   new_sha1, old_sha1, msg);
	return 0;
}