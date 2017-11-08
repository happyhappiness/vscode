static int files_transaction_abort(struct ref_store *ref_store,
				   struct ref_transaction *transaction,
				   struct strbuf *err)
{
	files_transaction_cleanup(transaction);
	return 0;
}