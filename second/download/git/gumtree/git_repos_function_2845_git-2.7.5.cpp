static struct ref_update *add_update(struct ref_transaction *transaction,
				     const char *refname)
{
	struct ref_update *update;
	FLEX_ALLOC_STR(update, refname, refname);
	ALLOC_GROW(transaction->updates, transaction->nr + 1, transaction->alloc);
	transaction->updates[transaction->nr++] = update;
	return update;
}