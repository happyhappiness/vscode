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