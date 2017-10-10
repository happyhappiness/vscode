	if (!dont_change_ref) {
		struct ref_transaction *transaction;
		struct strbuf err = STRBUF_INIT;

		transaction = ref_transaction_begin(&err);
		if (!transaction ||
		    ref_transaction_update(transaction, ref.buf,
					   sha1, forcing ? NULL : null_sha1,
					   0, msg, &err) ||
		    ref_transaction_commit(transaction, &err))
			die("%s", err.buf);
		ref_transaction_free(transaction);
		strbuf_release(&err);
	}

