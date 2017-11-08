struct ref_transaction *ref_store_transaction_begin(struct ref_store *refs,
						    struct strbuf *err)
{
	struct ref_transaction *tr;
	assert(err);

	tr = xcalloc(1, sizeof(struct ref_transaction));
	tr->ref_store = refs;
	return tr;
}