	if (check_refname_format(r->name, 0))
		return;

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_delete(transaction, r->name, r->sha1,
				   REF_ISPRUNING | REF_NODEREF, NULL, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		ref_transaction_free(transaction);
		error("%s", err.buf);
		strbuf_release(&err);
		return;
	}
