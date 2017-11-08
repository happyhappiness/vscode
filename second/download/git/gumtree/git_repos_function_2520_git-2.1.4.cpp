void ref_transaction_free(struct ref_transaction *transaction)
{
	int i;

	if (!transaction)
		return;

	for (i = 0; i < transaction->nr; i++)
		free(transaction->updates[i]);

	free(transaction->updates);
	free(transaction);
}