int initial_ref_transaction_commit(struct ref_transaction *transaction,
				   struct strbuf *err)
{
	struct ref_store *refs = transaction->ref_store;

	return refs->be->initial_transaction_commit(refs, transaction, err);
}