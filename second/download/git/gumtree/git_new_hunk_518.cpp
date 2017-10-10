		die("BUG: verify called with old_sha1 set to NULL");
	return ref_transaction_update(transaction, refname,
				      NULL, old_sha1,
				      flags, NULL, err);
}

int update_ref_oid(const char *msg, const char *refname,
	       const struct object_id *new_oid, const struct object_id *old_oid,
	       unsigned int flags, enum action_on_err onerr)
{
	return update_ref(msg, refname, new_oid ? new_oid->hash : NULL,
		old_oid ? old_oid->hash : NULL, flags, onerr);
}

int update_ref(const char *msg, const char *refname,
	       const unsigned char *new_sha1, const unsigned char *old_sha1,
	       unsigned int flags, enum action_on_err onerr)
{
	struct ref_transaction *t = NULL;
	struct strbuf err = STRBUF_INIT;
