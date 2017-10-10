			return -1;
		}
	}
	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, b->name, b->sha1, old_sha1,
				   0, msg, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		ref_transaction_free(transaction);
		error("%s", err.buf);
		strbuf_release(&err);
		return -1;
	}
