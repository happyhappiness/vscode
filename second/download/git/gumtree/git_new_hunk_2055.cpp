		have_old = 1;
	}

	if (*next != line_termination)
		die("delete %s: extra input: %s", refname, next);

	if (ref_transaction_delete(transaction, refname,
				   have_old ? old_sha1 : NULL,
				   update_flags, msg, &err))
		die("%s", err.buf);

	update_flags = 0;
	free(refname);
	strbuf_release(&err);

