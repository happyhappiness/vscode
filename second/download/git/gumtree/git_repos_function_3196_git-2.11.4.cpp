int ref_transaction_commit(struct ref_transaction *transaction,
			   struct strbuf *err)
{
	struct ref_store *refs = get_ref_store(NULL);

	return refs->be->transaction_commit(refs, transaction, err);
}