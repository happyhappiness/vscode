
	check_ref_valid(object, prev, ref, sizeof(ref), force);

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, ref, repl, prev,
				   0, 1, NULL, &err) ||
	    ref_transaction_commit(transaction, &err))
		die("%s", err.buf);

	ref_transaction_free(transaction);
	return 0;
}
