static struct ref_update *add_update(struct ref_transaction *transaction,
				     const char *refname)
{
	size_t len = strlen(refname);
	struct ref_update *update = xcalloc(1, sizeof(*update) + len + 1);

	strcpy((char *)update->refname, refname);
	ALLOC_GROW(transaction->updates, transaction->nr + 1, transaction->alloc);
	transaction->updates[transaction->nr++] = update;
	return update;
}