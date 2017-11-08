static struct ref_update *add_update(struct ref_transaction *transaction,
				     const char *refname)
{
	size_t len = strlen(refname) + 1;
	struct ref_update *update = xcalloc(1, sizeof(*update) + len);

	memcpy((char *)update->refname, refname, len); /* includes NUL */
	ALLOC_GROW(transaction->updates, transaction->nr + 1, transaction->alloc);
	transaction->updates[transaction->nr++] = update;
	return update;
}