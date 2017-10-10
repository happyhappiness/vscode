		goto cleanup;
	}
	for (t = first_tag; t; t = t->next_tag) {
		strbuf_reset(&ref_name);
		strbuf_addf(&ref_name, "refs/tags/%s", t->name);

		if (ref_transaction_update(transaction, ref_name.buf,
					   t->sha1, NULL, 0, msg, &err)) {
			failure |= error("%s", err.buf);
			goto cleanup;
		}
	}
	if (ref_transaction_commit(transaction, &err))
		failure |= error("%s", err.buf);
