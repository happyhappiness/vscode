	for (i = 0; i < targets; i++) {
		if (!write_ref[i])
			continue;
		strbuf_reset(&refname);
		strbuf_addf(&refname, "refs/%s", write_ref[i]);
		if (ref_transaction_update(transaction, refname.buf,
					   &sha1[20 * i], NULL, 0, 0,
					   msg ? msg : "fetch (unknown)",
					   &err)) {
			error("%s", err.buf);
			goto done;
		}
	}
