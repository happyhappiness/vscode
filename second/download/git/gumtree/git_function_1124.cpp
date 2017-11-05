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