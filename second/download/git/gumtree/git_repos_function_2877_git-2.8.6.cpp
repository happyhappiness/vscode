struct ref_transaction *ref_transaction_begin(struct strbuf *err)
{
	assert(err);

	return xcalloc(1, sizeof(struct ref_transaction));
}