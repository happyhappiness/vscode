struct ref_transaction *ref_transaction_begin(struct strbuf *err)
{
	return ref_store_transaction_begin(get_main_ref_store(), err);
}