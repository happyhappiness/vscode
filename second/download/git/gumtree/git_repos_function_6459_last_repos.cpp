static void files_transaction_cleanup(struct ref_transaction *transaction)
{
	size_t i;

	for (i = 0; i < transaction->nr; i++) {
		struct ref_update *update = transaction->updates[i];
		struct ref_lock *lock = update->backend_data;

		if (lock) {
			unlock_ref(lock);
			update->backend_data = NULL;
		}
	}

	transaction->state = REF_TRANSACTION_CLOSED;
}