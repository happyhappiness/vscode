struct ref_transaction *ref_transaction_begin(void)
{
	return xcalloc(1, sizeof(struct ref_transaction));
}