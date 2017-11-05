static int s_update_ref(const char *action,
			struct ref *ref,
			int check_old)
{
	char msg[1024];
	char *rla = getenv("GIT_REFLOG_ACTION");
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;
	int ret, df_conflict = 0;

	if (dry_run)
		return 0;
	if (!rla)
		rla = default_rla.buf;
	snprintf(msg, sizeof(msg), "%s: %s", rla, action);

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, ref->name, ref->new_sha1,
				   ref->old_sha1, 0, check_old, msg, &err))
		goto fail;

	ret = ref_transaction_commit(transaction, &err);
	if (ret) {
		df_conflict = (ret == TRANSACTION_NAME_CONFLICT);
		goto fail;
	}

	ref_transaction_free(transaction);
	strbuf_release(&err);
	return 0;
fail:
	ref_transaction_free(transaction);
	error("%s", err.buf);
	strbuf_release(&err);
	return df_conflict ? STORE_REF_ERROR_DF_CONFLICT
			   : STORE_REF_ERROR_OTHER;
}