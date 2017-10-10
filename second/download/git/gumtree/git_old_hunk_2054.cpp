	have_old = !parse_next_sha1(input, &next, old_sha1, "update", refname,
				    PARSE_SHA1_OLD);

	if (*next != line_termination)
		die("update %s: extra input: %s", refname, next);

	if (ref_transaction_update(transaction, refname, new_sha1, old_sha1,
				   update_flags, have_old, msg, &err))
		die("%s", err.buf);

	update_flags = 0;
	free(refname);
	strbuf_release(&err);

