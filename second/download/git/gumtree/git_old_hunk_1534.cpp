		  const char *logmsg)
{
	return refs_create_symref(get_main_ref_store(), ref_target,
				  refs_heads_master, logmsg);
}

int ref_transaction_commit(struct ref_transaction *transaction,
			   struct strbuf *err)
{
	struct ref_store *refs = transaction->ref_store;

	if (getenv(GIT_QUARANTINE_ENVIRONMENT)) {
		strbuf_addstr(err,
			      _("ref updates forbidden inside quarantine environment"));
		return -1;
	}

	return refs->be->transaction_commit(refs, transaction, err);
}

int refs_verify_refname_available(struct ref_store *refs,
				  const char *refname,
				  const struct string_list *extras,
				  const struct string_list *skip,
