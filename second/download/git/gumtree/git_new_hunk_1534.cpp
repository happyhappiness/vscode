		  const char *logmsg)
{
	return refs_create_symref(get_main_ref_store(), ref_target,
				  refs_heads_master, logmsg);
}

int ref_update_reject_duplicates(struct string_list *refnames,
				 struct strbuf *err)
{
	size_t i, n = refnames->nr;

	assert(err);

	for (i = 1; i < n; i++) {
		int cmp = strcmp(refnames->items[i - 1].string,
				 refnames->items[i].string);

		if (!cmp) {
			strbuf_addf(err,
				    "multiple updates for ref '%s' not allowed.",
				    refnames->items[i].string);
			return 1;
		} else if (cmp > 0) {
			die("BUG: ref_update_reject_duplicates() received unsorted list");
		}
	}
	return 0;
}

int ref_transaction_prepare(struct ref_transaction *transaction,
			    struct strbuf *err)
{
	struct ref_store *refs = transaction->ref_store;

	switch (transaction->state) {
	case REF_TRANSACTION_OPEN:
		/* Good. */
		break;
	case REF_TRANSACTION_PREPARED:
		die("BUG: prepare called twice on reference transaction");
		break;
	case REF_TRANSACTION_CLOSED:
		die("BUG: prepare called on a closed reference transaction");
		break;
	default:
		die("BUG: unexpected reference transaction state");
		break;
	}

	if (getenv(GIT_QUARANTINE_ENVIRONMENT)) {
		strbuf_addstr(err,
			      _("ref updates forbidden inside quarantine environment"));
		return -1;
	}

	return refs->be->transaction_prepare(refs, transaction, err);
}

int ref_transaction_abort(struct ref_transaction *transaction,
			  struct strbuf *err)
{
	struct ref_store *refs = transaction->ref_store;
	int ret = 0;

	switch (transaction->state) {
	case REF_TRANSACTION_OPEN:
		/* No need to abort explicitly. */
		break;
	case REF_TRANSACTION_PREPARED:
		ret = refs->be->transaction_abort(refs, transaction, err);
		break;
	case REF_TRANSACTION_CLOSED:
		die("BUG: abort called on a closed reference transaction");
		break;
	default:
		die("BUG: unexpected reference transaction state");
		break;
	}

	ref_transaction_free(transaction);
	return ret;
}

int ref_transaction_commit(struct ref_transaction *transaction,
			   struct strbuf *err)
{
	struct ref_store *refs = transaction->ref_store;
	int ret;

	switch (transaction->state) {
	case REF_TRANSACTION_OPEN:
		/* Need to prepare first. */
		ret = ref_transaction_prepare(transaction, err);
		if (ret)
			return ret;
		break;
	case REF_TRANSACTION_PREPARED:
		/* Fall through to finish. */
		break;
	case REF_TRANSACTION_CLOSED:
		die("BUG: commit called on a closed reference transaction");
		break;
	default:
		die("BUG: unexpected reference transaction state");
		break;
	}

	return refs->be->transaction_finish(refs, transaction, err);
}

int refs_verify_refname_available(struct ref_store *refs,
				  const char *refname,
				  const struct string_list *extras,
				  const struct string_list *skip,
